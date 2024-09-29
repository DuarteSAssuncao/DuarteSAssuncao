/**
 * @file graphics.c
 * @brief Definition of functions to handle the graphics (VBE)
 * @author T17_G1
 * @date 27/05/2024
 */

#include <lcom/lcf.h>
#include <machine/int86.h>
#include <stdlib.h>
#include "graphics.h"
#include "vbe.h"
#include <auxiliary/extra_utils.h>
#include <app/window.h>

#define DEBUG
#include <auxiliary/debug.h>

//! Screen
static window_t scr;
#define xres scr.width
#define yres scr.height
#define next_frame scr.buffer

//! Index of the next frame, number of buffers
static uint8_t next_frame_idx, n_buffers;

//! Pointer to a position in the video memory
static byte_t *video_mem;

//! Struct with the information about a certain video mode
static vbe_mode_info_t vmi;

//! The current video mode
static uint16_t mode_;

//! How many bytes per pixel the current mode requires
static uint8_t bytes_per_pixel;

//! The size of the frame buffer, the size of a line of the buffer
static size_t frame_buffer_size, frame_line_size;

//! Offset from coordinates (0, 0)
#define vg_offset(x,y,width) (bytes_per_pixel * (y * width + x))

//! Initializes a reg86_t struct with all registers set to 0
#define REG86_INIT() {.ah = 0}

/**
 * @brief Sets the mode using sys_int86()
 * @param uint16_t mode : the mode to set
 * @return int : 0 on success
 */
static int (vg_set_mode)(uint16_t mode) {
    reg86_t r = REG86_INIT();
    r.intno = BIOS_GRAPHICS_INT;
    r.ah = VBE_CALL;
    r.al = VBE_FUNC_SETMODE;
    r.bx = VBE_LINEAR | mode;
    if (sys_int86(&r))  // Returns 1 if there was an error
        return 1;
    mode_ = mode;
    return 0;
}

/**
 * @brief Allocates space for n_frames consecutive buffers for the specified video mode.
 * @param const vbe_mode_info_t *vmi_p : struct with the information about the mode
 * @param uint8_t n_frames : number of frames
 * @return void* : A pointer to the first pixel of the first buffer on success, NULL otherwise.
 */
void* (vg_alloc_buffer)(const vbe_mode_info_t *vmi_p, uint8_t n_frames) {
    if (vmi_p->NumberOfImagePages < n_frames - 1) return NULL; // mode does not support that many buffers

    size_t buffer_size = n_frames * ((vmi_p->BitsPerPixel + 7) / 8) * vmi_p->XResolution * vmi_p->YResolution;

    /* Get permission to map memory */
    struct minix_mem_range mr; /* physical memory range */
    mr.mr_base = (phys_bytes) vmi.PhysBasePtr;
    mr.mr_limit = mr.mr_base + buffer_size;
    if(sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)) return NULL;

    /* Map memory */
    void *res = vm_map_phys(SELF, (void *)mr.mr_base, buffer_size);
    if(res == MAP_FAILED) return NULL;

    return res;
}

/**
 * @brief Gets the information about the specified mode
 * @param uint16_t mode : the mode to get the information of
 * @param vbe_mode_info_t *vmi_p : a pointer to the struct to hold the information
 * @return int : 0 on success
 */
static int (vg_get_mode_info)(uint16_t mode, vbe_mode_info_t *vmi_p) {
    mmap_t vmi_map; // structure needed to get physical address of a pointer */
    if (lm_alloc(sizeof(*vmi_p), &vmi_map) == NULL) /* allocate space for a vbe_mode_info_t */
        return 1;

    reg86_t r = REG86_INIT();
    r.intno = BIOS_GRAPHICS_INT;
    r.ah = VBE_CALL;
    r.al = VBE_FUNC_GET_MODE_INFO;
    r.cx = mode;
    r.es = PB2BASE(vmi_map.phys);
    r.di = PB2OFF(vmi_map.phys);
    if (sys_int86(&r)) return 1;

    return memcpy(vmi_p, vmi_map.virt, sizeof(*vmi_p)) == NULL || !lm_free(&vmi_map);
}

/**
 * @brief Sets up the current mode to be used in the project, along with the allocated memory and constants
 * @param uint16_t mode : the mode to set
 * @return int : 0 on success
 */
int (vg_start)(uint16_t mode) {
    if (vg_get_mode_info(mode, &vmi)) return 1;
    scr.width = vmi.XResolution;
    scr.height = vmi.YResolution;
    bytes_per_pixel = (vmi.BitsPerPixel + 7) / 8;
    frame_line_size = xres * bytes_per_pixel;
    frame_buffer_size = yres * frame_line_size;

    if ((video_mem = vg_alloc_buffer(&vmi, n_buffers = 3)) == NULL) {
        DEBUG_PRINTF("VBE does not support 3 buffers\n");
        if ((video_mem = vg_alloc_buffer(&vmi, n_buffers = 2)) == NULL)
            return 1;
    }
    if (vg_set_mode(mode)) return 1;

    next_frame_idx = 1;
    next_frame = video_mem + frame_buffer_size * next_frame_idx;

    memset(video_mem, 0, 2 * frame_buffer_size);

    return 0;
}

/**
 * @brief Refresh the page by changing buffers
 * @return int : 0 on success
 */
int (vg_refresh)() {
    // page flipping -> swap current_frame and next_frame
    reg86_t r = {.ah = 0};
    r.intno = BIOS_GRAPHICS_INT; // 0x10
    r.ax = VBE_CALL_AX | VBE_FUNC_SET_GET_DISPLAY_START; // 0x4F07
    r.bl = 0x80; // Set Display Start during Vertical Retrace
    r.cx = 0;
    r.dx = next_frame_idx * yres;
    if (sys_int86(&r)) return 1;

    if (++next_frame_idx >= n_buffers)
        next_frame_idx = 0;
    next_frame = video_mem + next_frame_idx * frame_buffer_size;

    return 0;
}

/**
 * @brief Gets the pixel at the specified coordinates
 * @param uint16_t x : x-coordinates
 * @param uint16_t y : y-coordinates
 * @return byte_t* : pointer to the position in memory if existent
 */
static byte_t *(pixel_at)(uint16_t x, uint16_t y) {
    if (video_mem == NULL || x >= xres || y >= yres)
        return NULL;
    return next_frame + bytes_per_pixel * (y * xres + x);
}

/**
 * @brief Draw a horizontal line
 * @param uint16_t x : x-position of leftmost pixel
 * @param uint16_t y : depth of the line, i.e., distance from the top of the screen
 * @param uint16_t len : length of the line
 * @param uint32_t color : color of the line
 * @return int : 0 on success
 */
int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
    if (x > xres || y > yres) /* line is out of screen */
        return 0;
    len = min(len, xres - x);
    byte_t *begin = pixel_at(x,y), *end = pixel_at(x + len, y);

    if (begin == NULL || end == NULL) return 1;

    for (byte_t *pixel = begin; pixel != end; pixel += bytes_per_pixel)
        if (memcpy(pixel, &color, bytes_per_pixel) == NULL)
            return 1;
    return 0;
}

/**
 * @brief Draw a rectangle
 * @param uint16_t x : x-position of leftmost pixel
 * @param uint16_t y : y-position of upmost pixel
 * @param uint16_t width : width of the rectangle
 * @param uint16_t height : height of the rectangle
 * @param uint32_t color : color of the rectangle
 * @return int : 0 on success
 */
int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
    width = min(width, xres - x);
    height = min(height, yres - y);
    byte_t *p = pixel_at(x, y);
    if (!p) return 1;
    for (uint16_t a = 0; a < height; a++) {
        for (uint16_t b = 0; b < width; b++, p += bytes_per_pixel) {
            if (memcpy(p, &color, bytes_per_pixel) == NULL)
                return 1;
        }
        p += (xres - width) * bytes_per_pixel;
    }
    return 0;
}

/**
 * @brief Alternative, less fallible function to draw a rectangle
 * @param window_t *win : which window to draw the rectangle on
 * @param uint16_t x : x-position of leftmost pixel
 * @param uint16_t y : y-position of upmost pixel
 * @param uint16_t width : width of the rectangle
 * @param uint16_t height : height of the rectangle
 * @param uint32_t color : color of the rectangle
 * @return int : 0 on success
 */
int (draw_rect)(window_t *win, int16_t x, int16_t y, uint16_t width, uint16_t height, uint32_t color) {
    if (win == NULL) {
        if (scr.buffer == NULL) return 1;
        win = &scr;
    }
    if (x >= win->width || y >= win->height || x + width < 0 || y + height < 0) return 0; // successfully drawn nothing

    if (x < 0) {
        width += x;
        x = 0;
    }

    if (y < 0) {
        height += y;
        y = 0;
    }

    width = min(width, win->width - x);
    height = min(height, win->height - y);

    uint8_t *line_begin = win->buffer + vg_offset(x,y,win->width);

    size_t line_step = bytes_per_pixel * win->width;
    uint8_t *line_end = line_begin + height * line_step;

    for (uint8_t *line = line_begin; line != line_end; line += line_step) {
        uint8_t *end = line + width * bytes_per_pixel;
        for (uint8_t *pixel = line; pixel != end; pixel += bytes_per_pixel)
            memcpy(pixel, &color, bytes_per_pixel);
    }

    return 0;
}

/**
 * @brief Draw an image on a certain window
 * @param window_t *win : which window to draw the image on
 * @param uint8_t *image : image to draw
 * @param uint16_t width : width of the image
 * @param uint16_t height : height of the image
 * @param uint16_t x : x-position of leftmost pixel
 * @param uint16_t y : y-position of upmost pixel
 * @return int : 0 on success
 */
int (draw_image)(window_t *win, uint8_t *image, uint16_t width, uint16_t height, int16_t x, int16_t y) {
    if (win == NULL) {
        if (scr.buffer == NULL) return 1;
        win = &scr;
    }
    if (x >= win->width || y >= win->height) return 0; // successfully drawn nothing

    const uint8_t *sprite = image;
    uint16_t w, h; // actual size that will be put on the screen
    // the code below for X and Y is important to handle negative coordinates and pixmaps that go out of bounds
    if (x < 0) {
        if (width <= -x) return 0; // successfully drawn nothing
        sprite -= x * bytes_per_pixel; // skip the pixels that go out of bounds (on the left)
        if (width + x > win->width)
            w = win->width;
        else
            w = width + x;
        x = 0;
    } else w = min(width, win->width - x);

    if (y < 0) {
        if (height <= -y) return 0; // successfully drawn nothing
        sprite -= y * width * bytes_per_pixel; // skip the lines that go out of bounds (on the top)
        if (height + y > win->height)
            h = win->height;
        else
            h = height + y;
        y = 0;
    } else h = min(height, win->height - y);

    uint8_t *begin = win->buffer + vg_offset(x,y,win->width);
    size_t line_size = w * bytes_per_pixel;
    size_t line_step = win->width * bytes_per_pixel;
    size_t sprite_step = width * bytes_per_pixel;
    uint8_t *end = begin + h * line_step;

    for (uint8_t *line = begin; line < end; line += line_step, sprite += sprite_step) {
        memcpy(line, sprite, line_size);
    }

    return 0;
}

/**
 * @brief Draw a sprite on a certain window
 * @param window_t *win : which window to draw the sprite on
 * @param const sprite_t *img : sprite to draw
 * @param int16_t x : x-position of leftmost pixel
 * @param int16_t y : y-position of upmost pixel
 * @return int : 0 on success
 */
int (draw_sprite)(window_t *win, const xpm_image_t *img, int16_t x, int16_t y) {
    // not a macro because this might have some extra checks
    return draw_image(win, img->bytes, img->width, img->height, x, y);
}

/**
 * @brief Draws a transparent image on a certain window
 * @param window_t *window : window on where to draw
 * @param uint8_t *image : transparent image to draw
 * @param uint16_t width : width of the image
 * @param uint16_t height : height of the image
 * @param int16_t x : x-position of leftmost pixel
 * @param int16_t y : y-position of upmost pixel
 * @param uint32_t ignore : color to ignore, i.e., dCOLOR_BLACKraw as transparent
 * @return int : 0 on success
 */
int (draw_transparent_image)(window_t * window, uint8_t * image, uint16_t width, uint16_t height, uint16_t x, uint16_t y, uint32_t ignore) {
    if (window == NULL) {
        if (scr.buffer == NULL) return 1;
        window = &scr;
    }
    if (x >= window->width || y >= window->height) return 0; // successfully drawn nothing

    uint16_t leftmost = 0; // the leftmost column that will be visible on the screen
    uint16_t topmost = 0; // the topmost line that will be visible on the screen
    uint16_t w, h; // actual size that will be put on the screen
    // the code below for X and Y is important to handle negative coordinates and pixmaps that go out of bounds
    if (x < 0) {
        if (width <= -x) return 0; // successfully drawn nothing
        leftmost = -x;
        if (width + x > window->width)
            w = window->width;
        else
            w = width + x;
        x = 0;
    } else w = min(width, window->width - x);

    if (y < 0) {
        if (height <= -y) return 0; // successfully drawn nothing
        topmost = -y;
        if (height + y > window->height)
            h = window->height;
        else
            h = height + y;
        y = 0;
    } else h = min(height, window->height - y);

    for(uint16_t i = 0; i < w; i++) {
        for(uint16_t j = 0; j < h; j++) {
            uint8_t * pixel = window->buffer + ((y + j) * window->width + x + i) * bytes_per_pixel;
            const uint8_t * color = image + ((topmost + j) * width + leftmost + i) * bytes_per_pixel;
            if(memcmp(color, &ignore, bytes_per_pixel) == 0) continue;
            memcpy(pixel, color, bytes_per_pixel);
        }
    }

    return 0;
}

/**
 * @brief Fills the whole buffer
 * @param uint8_t *from : from where to copy
 * @return int : always 0
 */
int (vg_fill)(uint8_t *from) {
    memcpy(next_frame, from, frame_buffer_size);
    return 0; 
}

/**
 * @brief Clear the screen
 * @return int : 0 on success
 */
int (vg_clrscr)() {
    if (video_mem == NULL) return 1;
    return memset(next_frame, 0, frame_buffer_size) == NULL;
}

/**
 * @brief Returns to text mode
 * @return int : 0 on success
 */
int (vg_set_text_mode)() {
    if (video_mem == NULL) 
        return 0;

    reg86_t r = REG86_INIT();
    r.intno = BIOS_GRAPHICS_INT;
    r.ah = 0x00;
    r.al = 0x03;

    if (sys_int86(&r)) 
        return 1;

    video_mem = NULL;
    return 0;
}

/**
 * @brief Get the x-resolution of the current mode
 * @return uint16_t : x-resolution
 */
uint16_t (vg_get_xres)() {
    return xres;
}

/**
 * @brief Get the y-resolution of the current mode
 * @return uint16_t : y-resolution
 */
uint16_t (vg_get_yres)() {
    return yres;
}

/**
 * @brief Get the number of bytes per pixel
 * @return uint8_t : number of bytes per pixel
 */
uint8_t (vg_bytes_per_pixel)() {
    return bytes_per_pixel;
}

/**
 * @brief Get the size of the frame buffer
 * @return size_t : size of the frame buffer
 */
size_t (vg_frame_buffer_size)() {
    return frame_buffer_size;
}

/**
 * @brief Get the information about the color of the current mode
 * @return color_info_t : struct with information about the color
 */
color_info_t (vg_get_color_info)() {
    return (color_info_t) {
        .type = (vmi.RedMaskSize == 0) ? INDEXED : DIRECT,
        .RedMaskSize         = vmi.RedMaskSize,
        .RedFieldPosition    = vmi.RedFieldPosition,
        .GreenMaskSize       = vmi.GreenMaskSize,
        .GreenFieldPosition  = vmi.GreenFieldPosition,
        .BlueMaskSize        = vmi.BlueMaskSize,
        .BlueFieldPosition   = vmi.BlueFieldPosition,
        .RsvdMaskSize        = vmi.RsvdMaskSize,
        .RsvdFieldPosition   = vmi.RsvdFieldPosition,
        .DirectColorModeInfo = vmi.DirectColorModeInfo,
        .BitsPerPixel        = vmi.BitsPerPixel
    };
}
