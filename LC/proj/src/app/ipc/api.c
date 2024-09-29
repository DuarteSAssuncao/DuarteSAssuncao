/**
 * @file api.c
 * @brief Definition of functions related to windows (not the OS, thankfully)
 * @author T17_G1
 * @date 29/05/2024
 */

#include "api.h"
#include "client.h"
#include "protocol.h"
#include "messages.h"
#include <stdint.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include <auxiliary/extra_utils.h>

#define DEBUG
//#define DEBUG2
#include <auxiliary/debug.h>

//! Window at specified coordinates
#define win_at(win,x,y) ((win)->buf + (win)->attr.bytes_per_pixel * ((y) * (win)->attr.width + (x)))

/**
 * @brief Creates a window with initial attributes
 * @param const win_attr_t *init_attr : initial attributes
 * @return win_t* : pointer to window created, NULL if there was an error
 */
win_t* win_create(const win_attr_t *init_attr) {
    win_t *new_win = malloc(sizeof(*new_win));
    if (new_win == NULL) return NULL;
    *new_win = (win_t) {
        .server_fd = -1, .midman_fd = -1,
        .attr = init_attr != NULL ? *init_attr : (win_attr_t) {
            .width = 300,
            .height = 200,
            .x = 50,
            .y = 100,
            .bytes_per_pixel = 4,
            .n_buffers = 1,
        },
        .buf = WINBUF_ALLOC_FAIL
    };
    win_attr_t *attr = &new_win->attr;
    attr->frame_buffer_size = attr->width * attr->height * attr->bytes_per_pixel;

    DEBUG_INFOV("Connecting to middleman...\n");
    if ((new_win->midman_fd = rakoon_connect(MIDDLEMAN_SOCKET_ADDR, 10, 100)) == -1) goto win_create_fail;

    DEBUG_INFOV("Sending attr to middleman...\n");
    rakoon_msg_t msg = {.m_type = RKR_CREATE_WIN};
    memcpy(msg.data, attr, sizeof(*attr));
    if ((send(new_win->midman_fd, &msg, sizeof(msg), 0)) == -1) goto win_create_fail;

    DEBUG_INFOV("Connecting to main socket...\n");
    if ((new_win->server_fd = rakoon_connect(MAIN_SOCKET_ADDR, 10, 100)) == -1) goto win_create_fail;

    DEBUG_INFOV("Receiving attr from middleman...\n");
    if ((recv(new_win->midman_fd, &msg, sizeof(msg), 0)) == -1) goto win_create_fail;
    memcpy(attr, msg.data, sizeof(*attr));

    DEBUG_INFOV("Allocating frame buffer (win_id = %d)...\n", attr->win_id);
    new_win->buf = WINBUF_ALLOC(attr->win_id, attr->frame_buffer_size);
    if (new_win->buf == WINBUF_ALLOC_FAIL) goto win_create_fail;

    DEBUG_INFOV("Window memdump after creation:\n");
    DEBUG_MEMDUMP(new_win, sizeof(*new_win), 4);

    return new_win;

    /////////////////////

    win_create_fail:
    if (new_win->server_fd != -1) close(new_win->server_fd);
    if (new_win->midman_fd != -1) close(new_win->midman_fd);
    if (new_win->buf != WINBUF_ALLOC_FAIL) WINBUF_DEALLOC(new_win->buf);
    free(new_win);
    return NULL;
}

/**
 * @brief Closes a window
 * @param win_t *win : window to close
 * @return void
 */
void win_close(win_t *win) {
    if (win == NULL) return;
    if (win->server_fd != -1) close(win->server_fd);
    if (win->midman_fd != -1) close(win->midman_fd);
    if (win->buf != WINBUF_ALLOC_FAIL) WINBUF_DEALLOC(win->buf);
    free(win);
}

/**
 * @brief Get the width of the given window
 * @param const win_t *win : window to get the width of
 * @return uint16_t : width of the window
 */
uint16_t win_width(const win_t *win) {
    return win->attr.width;
}

/**
 * @brief Get the height of the given window
 * @param const win_t *win : window to get the height of
 * @return uint16_t : height of the window
 */
uint16_t win_height(const win_t *win) {
    return win->attr.height;
}

/**
 * @brief Get the x-position of the given window
 * @param const win_t *win : window to get the x-position of
 * @return uint16_t : x-position of the window
 */
int16_t win_x(const win_t *win) {
    return win->attr.x;
}

/**
 * @brief Get the y-position of the given window
 * @param const win_t *win : window to get the y-position of
 * @return uint16_t : y-position of the window
 */
int16_t win_y(const win_t *win) {
    return win->attr.y;
}

/**
 * @brief Refresh the given window
 * @param win_t *win : window to refresh (redraw)
 * @return int : 0 on success
 */
int win_refresh(win_t *win) {
    rakoon_msg_t msg = {.m_type = RKR_UPD_WIN, .win_id = win->attr.win_id};
    if (send(win->midman_fd, &msg, sizeof(msg), 0) == -1)
        return -1;
    DEBUG_INFOV("Requested refresh!\n");
    return 0;
}

#define BOX_OUT_OF_BOUNDS 1

/**
 * @brief Adjusts x, y, width and height to fit in the window
 * @return 0 if the box is visible on the screen, BOX_OUT_OF_BOUNDS if no pixel of the box is in the window.
 * @example If x = -5 and width = 10, x will be adjusted to 0 and width to 5
 */
static int evaluate_box(const win_t *win, int16_t *const x, int16_t *const y, int16_t *const width, int16_t *const height) {
    if (*width == 0 || *height == 0) return BOX_OUT_OF_BOUNDS;
    if (*width < 0) {
        *x += *width;
        *width = -*width;
    }

    if (*height < 0) {
        *y += *height;
        *height = -*height;
    }

    const win_attr_t *attr = &win->attr;
    if (*x >= attr->width || *y >= attr->height || *x + *width < 0 || *y + *height < 0) return BOX_OUT_OF_BOUNDS;

    if (*x < 0) {
        *width += *x;
        *x = 0;
    }

    if (*y < 0) {
        *height += *y;
        *y = 0;
    }

    *width = min(*width, attr->width - *x);
    *height = min(*height, attr->height - *y);
    return 0;
}

/**
 * @brief "Paste" a rectangle on a window
 * @param win_t *win : window to paste the rectangle on
 * @param int16_t x : x-position of the leftmost pixel of the rectangle
 * @param int16_t y : y-position of the upmost pixel of the rectangle
 * @param int16_t width : width of the rectangle
 * @param int16_t height : height of the rectangle
 * @param rgb_t color : color of the rectangle
 * @return int : 0 on success
 */
int win_paste_rect(win_t *win, int16_t x, int16_t y, int16_t width, int16_t height, rgb_t color) {
    color.unused = 0xff; // ensure it's opaque
    if (evaluate_box(win,&x,&y,&width,&height) == BOX_OUT_OF_BOUNDS)
        return 0; // successfully drawn nothing

    win_attr_t *attr = &win->attr;
    uint8_t bytes_per_pixel = attr->bytes_per_pixel;
    uint8_t *line_begin = win_at(win,x,y);
    size_t line_step = bytes_per_pixel * attr->width;
    uint8_t *line_end = line_begin + height * line_step;
    uint16_t bytes_copied_per_line = width * bytes_per_pixel;

    // draw a single line
    uint8_t *end = line_begin + bytes_copied_per_line;
    for (uint8_t *pixel = line_begin; pixel != end; pixel += bytes_per_pixel)
        memcpy(pixel, &color, bytes_per_pixel);

    // copy first line
    for (uint8_t *line = line_begin + line_step; line != line_end; line += line_step)
        memcpy(line, line_begin, bytes_copied_per_line);

    return 0;
}

/**
 * @brief Draw a rectangle on a window
 * @param win_t *win : window to draw the rectangle on
 * @param int16_t x : x-position of the leftmost pixel of the rectangle
 * @param int16_t y : y-position of the upmost pixel of the rectangle
 * @param int16_t width : width of the rectangle
 * @param int16_t height : height of the rectangle
 * @param argb_t color : color of the rectangle (with alpha channel)
 * @return int : 0 on success
 */
int win_draw_rect(win_t *win, int16_t x, int16_t y, int16_t width, int16_t height, argb_t color) {
    if (evaluate_box(win,&x,&y,&width,&height) == BOX_OUT_OF_BOUNDS)
        return 0; // successfully drawn nothing

    win_attr_t *attr = &win->attr;
    uint8_t bytes_per_pixel = attr->bytes_per_pixel;
    uint8_t *line_begin = win_at(win,x,y);
    size_t line_step = bytes_per_pixel * attr->width;
    uint8_t *line_end = line_begin + height * line_step;
    uint16_t bytes_copied_per_line = width * bytes_per_pixel;

    for (uint8_t *line = line_begin; line != line_end; line += line_step) {
        uint8_t *end = line + bytes_copied_per_line;
        for (uint8_t *pixel = line; pixel != end; pixel += bytes_per_pixel) {
            argb_t *background = (argb_t*) pixel;
            argb_t result = argb_blend(color, *background);
            memcpy(pixel, &result, bytes_per_pixel);
        }
    }

    return 0;
}

/**
 * @brief Draw a sprite on the specified window
 * @param win_t *win : window to draw the sprite on
 * @param const sprite_t *sprite : sprite to draw on the window
 * @param int16_t x : x-position of the leftmost pixel of the sprite
 * @param int16_t y : y-position of the upmost pixel of the sprite
 * @return int : always 0
 */
int win_draw_sprite(win_t *win, const sprite_t *sprite, int16_t x, int16_t y) {
    int16_t original_x = x, original_y = y;
    int16_t width = sprite->width, height = sprite->height;
    if (evaluate_box(win,&x,&y,&width,&height) == BOX_OUT_OF_BOUNDS)
        return 0; // successfully drawn nothing
    
    win_attr_t *attr = &win->attr;
    uint8_t bytes_per_pixel = attr->bytes_per_pixel;
    uint8_t *lines_begin = win_at(win,x,y);
    size_t line_step = bytes_per_pixel * attr->width;
    uint8_t *lines_end = lines_begin + height * line_step;
    uint16_t bytes_copied_per_line = width * bytes_per_pixel;

    argb_t *sprite_begin = sprite_at(*sprite, x - original_x, y - original_y);
    size_t sprite_line_step = sprite->width;

    argb_t *sprite_line = sprite_begin;
    for (uint8_t *line = lines_begin; line != lines_end; line += line_step, sprite_line += sprite_line_step) {
        uint8_t *end = line + bytes_copied_per_line;
        argb_t *sprite_ptr = sprite_line;
        for (uint8_t *pixel = line; pixel != end; pixel += bytes_per_pixel, ++sprite_ptr) {
            argb_t *background = (argb_t*) pixel;
            if (sprite_ptr->a != 0)
                *background = argb_blend(*sprite_ptr, *background);
        }
    }

    return 0;
}

/**
 * @brief Draw a scaled sprite on the given window
 * @param win_t *win : window to draw the scaled sprite on
 * @param const sprite_t *sprite : sprite to draw the window (initially unscaled)
 * @param int16_t x : x-position of the leftmost pixel of the sprite
 * @param int16_t y : y-position of the upmost pixel of the sprite
 * @param uint16_t scale : scale to multiply the sprite dimensions with
 * @return int : always 0
 */
int win_draw_sprite_scaled(win_t *win, const sprite_t *sprite, int16_t x, int16_t y, uint16_t scale) {

    // CAN BE OPTIMIZED

    for (int16_t j = 0; j < sprite->height * scale; ++j) {
        if (y + j < 0)
            continue;
        else if (y + j >= win->attr.height)
            break;

        for (int16_t i = 0; i < sprite->width * scale; ++i) {
            if (x + i < 0)
                continue;
            else if (x + i >= win->attr.width)
                break;

            argb_t *background = (argb_t*) win_at(win,x+i,y+j);
            *background = argb_blend(*sprite_at(*sprite, i / scale, j / scale), *background);
        }
    }
    return 0;
}

/**
 * @brief Draws a text on the window
 * @param win_t *win : window to draw the text on
 * @param const char *text : C-string to draw
 * @param const sprite_t char_sprites[256] : an array of monospaced sprites for each char value
 * @param int16_t x : X coordinate of the top-left pixel of the text on the window
 * @param int16_t y : Y coordinate of the top-left pixel of the text on the window
 * @param uint16_t max_width : Maximum width that the text can take
 * @param uint16_t scale : Scale of the text (1 for original, 2 for double width and height, and so on)
 * @param void (*if_too_long)(const char *, char *, size_t) : If not NULL, will be called whenever the text is too long
 *                    First parameter (const char*) : the original text
 *                    Second parameter (char*) : pointer to a copy of the N first characters that fit (are modifiable)
 *                    Third parameter (size_t) : N
 * @param bool center : If true, the string will be centered. Otherwise, it will be aligned to the left
 * @return int : 0 on success, non-zero otherwise
 */
int win_draw_text(win_t *win, const char *text, const sprite_t char_sprites[256], int16_t x, int16_t y, uint16_t max_width, uint16_t scale, void (*if_too_long)(const char *, char *, size_t), bool center) {
    uint16_t spacing = 1; // pixels between letters (will be scaled)
    uint16_t sprite_width = char_sprites->width;
    uint16_t pixels_per_char = (sprite_width + spacing) * scale;

    int max_chars = max_width / pixels_per_char;
    DEBUG_PRINTF2("max_chars = %d\n", max_chars);
    char str[max_chars + 1]; // Warning: Variable-Length Arrays (VLA) are not widely supported
    str[max_chars] = '\0';
    strncpy(str, text, max_chars + 1);

    if (str[max_chars] != '\0' && if_too_long != NULL) { // null terminator overriden -> text too big
        str[max_chars] = '\0';
        if_too_long(text, str, max_chars);
    }

    DEBUG_PRINTF2("str= \"%s\"\n", str);

    int len = strlen(str);
    int pos;
    if (center)
        pos = x + (max_width / 2) - (len * pixels_per_char) / 2;
    else
        pos = x;

    for (int i = 0; i < len; ++i) {
        const sprite_t *letter = &char_sprites[(int) str[i]];
        win_draw_sprite_scaled(win, letter,
            pos + (i * pixels_per_char),
            y,
            scale
        );
    }

    return 0;
}

/**
 * @brief Draw a line on the given window using the Bresenham's Line Algorithm
 * @param win_t *win : window to draw the line on
 * @param int16_t x1 : x-position of start of line
 * @param int16_t y1 : y-position of end of line
 * @param int16_t x2 : x-position of start of line
 * @param int16_t y2 : y-position of end of line
 * @param argb_t color : color of the line
 * @return int : always 0
 */
int win_draw_line(win_t *win, int16_t x1, int16_t y1, int16_t x2, int16_t y2, argb_t color) {

    // Bresenham's Line Algorithm (https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int error = dx - dy;

    while (1) {
        win_draw_pixel(win,x1,y1,color);

        if (x1 == x2 && y1 == y2) break;

        int e2 = 2 * error;
        if (e2 > -dy) {
            error -= dy;
            x1 += sx;
        }

        if (e2 < dx) {
            error += dx;
            y1 += sy;
        }
    }

    return 0;
}

/**
 * @brief Draw a pixel on the given window
 * @param win_t *win : window to draw the pixel on
 * @param int16_t x : x-position of the pixel
 * @param int16_t y : y-position of the pixel
 * @param argb_t color : color of the pixel
 * @return int : always 0
 */
int win_draw_pixel(win_t *win, int16_t x, int16_t y, argb_t color) {
    if (x < 0 || y < 0 || x >= win->attr.width || y >= win->attr.height)
        return 0;
    argb_t *background = (argb_t*) win_at(win,x,y);
    *background = argb_blend(color, *background);
    return 0;
}

/**
 * @brief Waits for an event in a window, blocking the current thread
 * @param win_t *win : window to wait for an event on
 * @param rakoon_msg_t *msg : where to store the event
 * @return int : 0 on success
 */
int win_wait_event(win_t *win, rakoon_msg_t *msg) {
    int n_bytes = recv(win->midman_fd, msg, sizeof(*msg), 0);
    if (n_bytes > 0) return 0;
    if (n_bytes == 0) {
        DEBUG_WARNV("Rakoon shutdown?\n");
        msg->m_type = RKE_SHUTDOWN;
        return 0;
    }
    DEBUG_ERRORV("%s\n", strerror(errno));
    return -1;
}

#include <fcntl.h>

static int start_serial_port(const win_t *win, uint8_t type, const char *fullpath) {
    int fd;
    // open the file to check for permissions (can easily be exploited by just not using this function, though)
    switch (type) {
        case RKR_RECEIVE_SERIAL_PORT_FILE: fd = open(fullpath, O_WRONLY | O_CREAT); break;
        case RKR_SEND_SERIAL_PORT_FILE: fd = open(fullpath, O_RDONLY); break;
        default:
            errno = EINVAL;
            DEBUG_PERRORV("");
            return -1;
    }

    DEBUG_INFOV("%s\n", type == RKR_SEND_SERIAL_PORT_FILE ? "RKR_SEND_SERIAL_PORT_FILE" : "RKR_RECEIVE_SERIAL_PORT_FILE");

    if (fd == -1) {
        DEBUG_PERRORV("open");
        return -1;
    }
    close(fd);

    FILE *fp = fopen(SERIAL_PORT_PATH, "w");
    if (fp == NULL) {
        DEBUG_PERRORV("fopen");
        return -1;
    }
    DEBUG_INFOV("Sending full path \"%s\"...\n", fullpath);
    fprintf(fp, "%s", fullpath);
    fclose(fp);

    rakoon_msg_t msg = {.m_type = type, .win_id = win->attr.win_id};
    int retv = send(win->midman_fd, &msg, sizeof(msg), 0);
    if (retv == -1)
        DEBUG_PERRORV("send");
    return retv <= 0;
}

int send_file_through_serial_port(const win_t *win, const char *fullpath) {
    return start_serial_port(win, RKR_SEND_SERIAL_PORT_FILE, fullpath);
}

int receive_file_through_serial_port(const win_t *win, const char *fullpath) {
    return start_serial_port(win, RKR_RECEIVE_SERIAL_PORT_FILE, fullpath);
}
