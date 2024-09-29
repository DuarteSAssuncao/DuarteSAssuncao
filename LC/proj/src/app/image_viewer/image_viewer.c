#include <lcom/lcf.h>
#include <stdio.h>
#include <stdbool.h>
#include "cbmp.h"
#include "../ipc/api.h" // window api
#include "../../graphics/color.h"

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

    BMP* bmp = bopen(argv[1]);
    uint16_t i_width = get_width(bmp);
    uint16_t i_height = get_height(bmp);

    win_attr_t attr = {
        .x = 400, // rand() % 1152 + 400,
        .y = 90, // rand() % 864 + 90,
        .width = 650, // 150 + rand() % 650,
        .height = 500, // 100 + rand() % 500,
    };

    win_t *win = win_create(&attr);
    if (win == NULL) {
        perror("win_create");
        return 1;
    }

    uint32_t black = 0xFF000000;
    for(uint32_t i = 0; i < attr.width * attr.height; i++) {
        memcpy(win->buf, &black, attr.bytes_per_pixel);
    }

    int x = (attr.width - i_width) / 2;
    if(x < 0) x = 0;
    int y = (attr.height - i_height) / 2;
    if(y < 0) y = 0;

    uint16_t y_max = i_height < attr.height ? i_height : attr.height;
    for(uint16_t i = 0; i < i_width && i < attr.width; i++) {
        for(uint16_t j = 0; j < i_height && j < attr.height; j++) {
            uint8_t r, g, b;
            get_pixel_rgb(bmp, i, j, &r, &g, &b);
            argb_t * pixel = (argb_t*) (win->buf + win->attr.bytes_per_pixel * ((y + y_max - j - 1) * win->attr.width + x + i));
            argb_t color = {
                .a = 0xFF,
                .r = r,
                .b = b,
                .g = g
            };
            *pixel = argb_blend(color, *pixel);
        }
    }

    if (win_refresh(win)) {
        perror("win_refresh");
        return 1;
    }

    bool end = false;
    while(!end) {
        rakoon_msg_t msg;
        if (win_wait_event(win, &msg)) {
            perror("win_wait_event");
            break;
        }

        switch (msg.m_type) {
            case RKE_SHUTDOWN:
            case RKE_CLOSE_WIN:
                end = true;
                break;
        
            default: break;
        }
    }

    win_close(win);
    bclose(bmp);

    return 0;
}
