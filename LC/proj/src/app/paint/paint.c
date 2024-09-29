/**
 * @file paint.c
 * @brief Simple painting app
 * @author T17_G1
 * @date 02/06/2024
 */

#include <app/ipc/api.h>
#include <stdio.h>
#include <stdbool.h>

/**
 * @brief Main function of Paint
 * @return int : 0 on success
 */
int main() {
    win_t *win = win_create(NULL);
    if (win == NULL) {
        perror("win_create");
        return 1;
    }

    win_fill_rgb(win, (rgb_t) {.hex = 0xeeeeee});
    win_refresh(win);

    bool end = false;
    while (!end) {
        rakoon_msg_t msg;
        win_wait_event(win, &msg);

        switch (msg.m_type) {
            case RKE_MOUSE: {
                mouse_data_t *info = (mouse_data_t*) msg.data;
                switch (info->type) {
                    case MOUSE_LEFT_CLICK:
                    case MOUSE_LEFT_DRAG_START:
                    case MOUSE_LEFT_DRAG:
                        win_draw_line(win, info->x, info->y, info->x - info->dx, info->y - info->dy, (argb_t) {.hex = 0xff000000});
                        win_refresh(win);
                        break;
                    default:
                        break;
                }
                break;
            }
            case RKE_SHUTDOWN:
                end = true;
                break;
            default:
                break;
        }
    }
    win_close(win);
    return 0;
}
