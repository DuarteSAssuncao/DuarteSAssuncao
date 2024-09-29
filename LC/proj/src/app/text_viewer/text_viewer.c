#include <lcom/lcf.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../ipc/api.h" // window api
#include "../../graphics/color.h"
#include "../file_explorer/file_expl_draw.h"
#include "../../auxiliary/vector.h"
#include "../../auxiliary/debug.h"

#define DEBUG

// TODO: Documentation!
typedef struct line {
    uint32_t line_no;
    size_t length;
    long file_pos;
} line_t;

typedef vector(line_t) line_vector_t;

// TODO: Documentation!
static int fill_lines(line_vector_t * lines, FILE * fp, uint8_t scale, uint16_t line_width);

// TODO: Documentation!
static int draw_lines(line_vector_t * lines, FILE * fp, uint32_t begin, win_t *win, uint8_t scale);

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <full path>\n", argv[0]);
        exit(1);
    }

    const char *fullpath = argv[1];

    if (fullpath[0] != '/') {
        fprintf(stderr, "%s: Path provided (\"%s\") is not a full path (it should start with '/')\n", argv[0], fullpath);
        return 1;
    }

    if (file_expl_load_sprites()) {
        perror("file_expl_load_sprites");
        exit(1);
    }

    win_attr_t attr = {
        .x = 90, // rand() % 1152 + 400,
        .y = 90, // rand() % 864 + 90,
        .width = 550, // 150 + rand() % 550,
        .height = 700, // 100 + rand() % 700,
    };

    win_t *win = win_create(&attr);
    if (win == NULL) {
        perror("win_create");
        return 1;
    }

    FILE * fp = fopen(fullpath, "r+");
    if (fp == NULL) {
        fprintf(stderr, "Unable to open %s file\n", fullpath);
        return 1;
    }

    win_draw_text(
        win,
        fullpath,
        black_char_sprites,
        10, 5,
        win->attr.width - 20,
        2, NULL, true
    );
    
    line_vector_t lines;
    vector_init_cap(&lines, 40);
    fill_lines(&lines, fp, 2, win->attr.width - 20); // the '-20' is for a padding of 10 on the left and right
    uint32_t first_line_on_screen = 1;
    draw_lines(&lines, fp, first_line_on_screen, win, 2);
    if (win_refresh(win)) {
        perror("win_refresh");
        return 1;
    }

    keyboard_data_t kb_info;
    bool end = false;
    bool refresh = false;
    while(!end) {
        rakoon_msg_t msg;
        if (win_wait_event(win, &msg)) {
            perror("win_wait_event");
            break;
        }

        switch (msg.m_type) {
            case RKE_KEYBOARD:
                memcpy(&kb_info, msg.data, sizeof(kb_info));
                if (kb_info.release)
                    break;
                else {
                    switch (kb_info.code) {
                        case KEY_ARROW_UP:
                            if(first_line_on_screen != 1) {
                                first_line_on_screen--;
                                refresh = true;
                            }
                            break;
                        case KEY_ARROW_DOWN:
                            if(first_line_on_screen != lines.size) {
                                first_line_on_screen++;
                                refresh = true;
                            }
                            break;
                        default:
                            break;
                    }
                }
                break;

            case RKE_SHUTDOWN:
            case RKE_CLOSE_WIN:
                end = true;
                break;
        
            default: break;
        }
        if (refresh) {
            draw_lines(&lines, fp, first_line_on_screen, win, 2);
            if (win_refresh(win)) {
                perror("win_refresh");
                return 1;
            }
            refresh = false;
        }
    }

    win_close(win);
    vector_destruct(&lines);
    fclose(fp);

    return 0;
}

static int fill_lines(line_vector_t * lines, FILE * fp, uint8_t scale, uint16_t line_width) {
    char buf[256];
    if(line_width > 1152) line_width = 1152;
    uint8_t chars_per_line = line_width / (7 * scale);
    long pos = ftell(fp);
    uint32_t n = 1;
    while(fgets(buf, chars_per_line + 1, fp) != NULL) {
        vector_extend(lines);
        line_t * l = (line_t *)lines->at + lines->size - 1;
        l->file_pos = n;
        l->length = strlen(buf);
        l->file_pos = pos;

        pos = ftell(fp);
        if(pos < 0) return pos;
        n++;
    }
    return 0;
}

static int draw_lines(line_vector_t * lines, FILE * fp, uint32_t begin, win_t *win, uint8_t scale) {
    win_fill_rgb(win, (rgb_t) {.hex = 0xFFFFFF});
    uint16_t y = 5 + 11 * 2 + 5; // Leaving space for the file name at the top. WARNING: Hardcoded!
    uint8_t max_lines = (win->attr.height - y) / (13 * scale); // Leaving a space between lines of 2 * scale pixels. WARNING: Hardcoded!

    for(uint8_t i = begin - 1; i < max_lines && i < lines->size; i++) {
        line_t * line = (line_t *)lines->at + i;
        if(fseek(fp, line->file_pos, SEEK_SET) != 0) {
            DEBUG_ERRORV("Invalid file position (%d)\n", line->file_pos);
            return 1;
        }
        
        char buf[256];
        if(fgets(buf, line->length + 1, fp) != buf) {
            fprintf(stdout, "Error reading from file\n");
            return 1;
        }

        if(buf[strlen(buf) - 1] == '\n') buf[strlen(buf) - 1] = '\0';

        win_draw_text(
            win, buf,
            black_char_sprites,
            10, y + ((i - begin + 1) * 13 * scale), // Leaving a space between lines of 2 * scale pixels. WARNING: Hardcoded!
            win->attr.width - 20,
            scale, NULL, false
        );
    }
    return 0;
}
