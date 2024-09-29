/**
 * @file setup.c
 * @brief Sets up the components of the project. Most functions accept "int argc, char **argv" and return "int"
 * @author T17_G1
 * @date 27/05/2024
 */

#include "setup.h"
#include "shared.h"
#include "app_timer.h"
#include "app_keyboard.h"
#include "app_mouse.h"
#include "app_rtc.h"
#include "app_serial_port.h"
#include <graphics/graphics.h>
#include <graphics/icons.h>
#include <graphics/vbe_modes.h>
#include <interrupts/interrupts.h>
#include <lab6/rtc.h>
#include <stdlib.h>
#include <serial_port/uart.h>
#include <serial_port/serial_port.h>
#include <interrupts/keyboard.h>
#include <interrupts/kbc_i8042.h>
#include "ipc/server.h"
#include <interrupts/timer.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <serial_port/sp_ih.h>

#define DEBUG
#include <auxiliary/debug.h>

#include <stdio.h>
#include <stdint.h>

/**
 * @brief Cleans up the program by freeing memory, disabling subscriptions and returning to text mode
 * @return int : 0 on success
 */
int (prog_cleanup)() {
    free_dir_node_and_descendants(home);
    vg_set_text_mode();
    interrupts_disable_all();
    free(background.buffer);

    for(int i = n_fe - 1; i >= 0; i--) {
        if(close_fe_window(file_explorers + i * sizeof(*file_explorers)) != 0) return 1;
    }
    for(int i = n_windows - 1; i >= 0; i--) {
        if(close_window(windows + i * sizeof(*windows)) != 0) return 1;
    }

    server_cleanup();
    return 0;
}

/**
 * @brief Loads all available interruptions (subscribed device with a custom interrupt handler)
 * @return int : 0 on success
 */
static int (load_interrupts)() {
    for (device_t device = 0; device < DEVICE_COUNT; ++device) {
        if (handlers[device] == NULL) {
            DEBUG_PRINTF("handlers[%d] (%s) is NULL, ignoring...\n", device, device_to_str(device));
            continue;
        }
        int retv = interrupts_enable(device, handlers[device]);
        if (retv) {
            DEBUG_PRINTF("Failed to enable %s: %s\n", device_to_str(device), int_strerror(retv));
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Retrieves the home directory provided by main.c, then prints its content and loads interrupts
 * @param int argc : number of arguments passed to the function
 * @param char **argv : array of arguments passed to the function
 * @return int : 0 on success
 */
int (proj_setup)(int argc, char **argv) {
    FILE * file;

    TRY(home = calloc(1, sizeof(*home)),            ==NULL, strerror(errno), 1,);
    TRY(file = fopen(SHARED_FILE, "r"),             ==NULL, strerror(errno), 1,);
    TRY(fgets(home->fullpath, PATH_MAX, file),      ==NULL, "return value is NULL", 1,);
    TRY(fclose(file),                               ==EOF, strerror(errno), 1,);
    TRY(load_dir(home->fullpath, &curdir_items),    !=0, strerror(errno), 1,);
    TRY(chdir(home->fullpath),                      !=0, strerror(errno),1,);
    TRY(setenv("HOME", home->fullpath, 1),          !=0, strerror(errno),1,);

    curdir = home;

    handlers[KEYBOARD] = proj_keyboard_handler;
    if (load_interrupts())
        return 1;

    print_dir_items(&curdir_items);
    printf("Type directory: ");

    return 0;
}

/**
 * @brief This function sets up a penguin
 * @param int argc : number of arguments passed to the function
 * @param char **argv : array of arguments passed to the function
 * @return int : 0 on success
 */
int (penguin_setup)(int argc, char **argv) {
    if (xpm_load(penguin, XPM_INDEXED, &penguin_sprite) == NULL) return 1;
    if (vg_start(VBE_INDEXED_1024x768)) return 1;

    penguin_x = vg_get_xres() / 4, penguin_y = vg_get_yres() / 4;

    handlers[TIMER] = timer_handler,
    handlers[KEYBOARD] = penguin_keyboard_handler,
    handlers[MOUSE] = penguin_mouse_handler;
    if (load_interrupts()) return 1;
    return 0;
}

/**
 * @brief Debug setup function for the keyboard
 * @param int argc : number of arguments passed to the function
 * @param char **argv : array of arguments passed to the function
 * @return int : 0 on success
 */
int (keyboard_debug_setup)(int argc, char **argv) {
    handlers[KEYBOARD] = debug_keyboard_handler, handlers[TIMER] = timer_handler;
    if (load_interrupts()) return 1;
    return 0;
}

/**
 * @brief Test function for the Real Time Clock
 * @param int argc : number of arguments passed to the function
 * @param char **argv : array of arguments passed to the function
 * @return int : 0 on success
 */
int (rtc_test)(int argc, char **argv) {
    if (argc != 1) goto rtc_test_invalid_arg;

    TRY(rtc_init(),             != 0, "error", 1,);

    if (!strcmp(argv[0], "config")) {
        uint8_t config[4];
        rtc_get_config(config);

        for (int i = 0; i < 4; ++i) {
            printf("Register %c: 0x%02x (0b", 'A' + i, config[i]);

            // print in binary
            for (uint8_t bit = BIT(7); bit != 0; bit >>= 1)
                printf("%c", bit & config[i] ? '1' : '0');

            printf(")\n");
        }
    }

    else if (!strcmp(argv[0], "date")) {
        date_t date;
        if (rtc_get_date(&date)) return 1;
        printf("%d/%02d/%02d, %02d:%02d:%02d", /*weekday_to_str(date.weekday)*/ 2000 + date.year,
                date.month, date.day, date.hour, date.min, date.sec
              );
    }

    else if (!strcmp(argv[0], "int")) {
        handlers[RTC] = rtc_test_handler, handlers[KEYBOARD] = penguin_keyboard_handler;
        if (load_interrupts()) return 1;

        date_t date;
        TRY(rtc_get_date(&date),                                        != 0, "error", 1,);
        TRY(rtc_enable_alarm(RTC_ALARM_IGNORE, RTC_ALARM_IGNORE, 0),    != 0, "error", 1,);
        TRY(rtc_enable_update_interrupts(),                             != 0, "error", 1,);
        TRY(rtc_enable_periodic_interrupts(1),                          != 0, "error", 1,);
    } else { rtc_test_invalid_arg:
        printf(
                "Invalid argument(s) provided. Available setups:\n"
                "\t./main \"rtc config\": Prints the 4 registers related to the RTC configuration\n"
                "\t./main \"rtc date\": Prints the current date\n"
                "\t./main \"rtc int\": Tests interrupts with the RTC\n"
              );
        return 1;
    }

    return 0;
}

/**
 * @brief Sets up windows (not the OS)
 * @param int argc : number of arguments passed to the function
 * @param char **argv : array of arguments passed to the function
 * @return int : 0 on success
 */
int (windows_setup)(int argc, char **argv) {
    time_t t = time(NULL);
    DEBUG_PRINTF("Random Seed: %zd\n", t);
    srand(t);
    handlers[KEYBOARD] = windows_keyboard_handler;
    handlers[MOUSE] = windows_mouse_handler;
    handlers[TIMER] = timer_windows_handler;
    handlers[RTC] = rtc_handler;
    if (rtc_enable_update_interrupts()) return -1;
    if (load_interrupts()) return 1;

    FILE * file;
    TRY(home = calloc(1, sizeof(*home)),            ==NULL, strerror(errno), 1,);
    TRY(file = fopen(SHARED_FILE, "r"),             ==NULL, strerror(errno), 1,);
    TRY(fgets(home->fullpath, PATH_MAX, file),      ==NULL, "return value is NULL", 1,);
    TRY(fclose(file),                               ==EOF, strerror(errno), 1,);
    TRY(load_dir(home->fullpath, &curdir_items),    !=0, strerror(errno), 1,);
    TRY(chdir(home->fullpath),                      !=0, strerror(errno),1,);
    TRY(setenv("HOME", home->fullpath, 1),          !=0, strerror(errno),1,);
    curdir = home;

    TRY(vg_start(VBE_8_8_8_8_1152x864),                                     != 0, "error", 1,);
    background = (window_t) {
        .width = vg_get_xres(),
        .height = vg_get_yres(),
        .buffer = calloc(1, vg_frame_buffer_size())
    };

    draw_background();
    draw_folders();
    vg_fill(background.buffer);
    vg_refresh();

    mouse_sprite = xpm_load(mouse_xpm, XPM_8_8_8_8, &mouse_sprite_info);
    if (mouse_sprite == NULL) return 1;

    return 0;
}

/**
 * @brief Sets up the IPC (Inter-Process Communication)
 * @param int argc : number of arguments passed to the function
 * @param char **argv : array of arguments passed to the function
 * @return int : 0 on success
 */
int ipc_setup(int argc, char **argv) {
    TRY(timer_init(),                                                       !=0, strerror(errno),1,);
    TRY(server_init(),                                                      !=0, strerror(errno),1,);

    handlers[KEYBOARD] = ipc_keyboard_handler;
    handlers[MOUSE] = ipc_mouse_handler;
    handlers[TIMER] = ipc_timer_handler;
    handlers[RTC] = rtc_handler;
    handlers[SERIAL_PORT] = sp_proj_handler;
    if (rtc_enable_alarm(RTC_ALARM_IGNORE, RTC_ALARM_IGNORE, 0)) return -1;
    if (rtc_get_date(&date)) return -1;
    update_clock = true;
    if (rtc_enable_update_interrupts()) return -1;
    if (load_interrupts()) return 1;

    TRY(vg_start(VBE_8_8_8_8_1152x864),                                     != 0, "error", 1,);
    background = (window_t) {
        .width = vg_get_xres(),
        .height = vg_get_yres(),
        .buffer = calloc(1, vg_frame_buffer_size()),
    };

    load_top_bar();
    vg_refresh();

    mouse_sprite = NULL;
    mouse_sprite = xpm_load(mouse_xpm, XPM_8_8_8_8, &mouse_sprite_info);
    if (mouse_sprite == NULL) return 1;

    cross_sprite = NULL;
    cross_sprite = xpm_load(close_window_icon, XPM_8_8_8_8, &cross_sprite_info);
    if(cross_sprite == NULL) return 1;

    return 0;
}

#include <serial_port/sp_util.h>
/**
 * @brief Can either create a chat or transfer a file. Used for standalone purposes (i.e., without the desktop environment)
 * @note This function is never used at the same time as the project. Due to time constraints, the Serial Port couldn't be totally implemented in Rakoon - you can use it here instead
 * @param int argc : number of arguments passed to the function
 * @param char **argv : array of arguments passed to the function
 * @return int : 0 on success
 */
int serial_port(int argc, char **argv) {
    if (argc >= 1) {
        if (!strcmp(argv[0], "chat"))
            chat(argc >= 2 ? argv[1] : "You", argc >= 3 ? argv[2] : "Other");
        else if (!strcmp(argv[0], "file_transfer") && argc >= 4)
            file_transfer((uint8_t) atoi(argv[1]), argv[2], argv[3]);
        else {
            printf("Invalid operation: %s\n", argv[0]);
            return 1;
        }
    } else {
        printf("No operation was chosen\n");
        return 1;
    }
    send_delay(0x00);
    return 0;
    /*
    uint8_t kbit = 1, sbit = 4;
    int s_id = subscribe(COM1_IRQ, IRQ_REENABLE, &sbit);
    int k_id = subscribe(1, IRQ_REENABLE | IRQ_EXCLUSIVE, &kbit);
    message msg;
    int ipc_status = 0;
    
    FILE* from = fopen("/home/lcom/labs/original.txt", "r");
    FILE* to = fopen("/home/lcom/labs/copy.txt", "w");
    set_origin_file(from);
    set_destination_file(to);
    if (!strcmp(argv[0],"receiver"))
        set_stance(RECEIVER);
    else
        set_stance(SENDER);
    
    set_stance(CHAT);
    while (true) {
        while (driver_receive(ANY, &msg, &ipc_status));
        if (is_ipc_notify(ipc_status) && _ENDPOINT_P(msg.m_source) == HARDWARE) {
            if (msg.m_notify.interrupts & BIT(sbit)) {
                serial_ih();
                if (get_stance() == SLEEP) {
                    send_delay(0x00);
                    goto end;
                }
                    
            }
            if (msg.m_notify.interrupts & BIT(kbit)) {
                uint32_t c = 0;
                sys_inb(0x60, &c);
                if (!(c & BIT(8)))
                    send_char_sp(keycode_to_char(c));
            }
        }

    }
    printf("Gotten out\n");
    unsubscribe(&s_id);
    printf("Serial port unsubscribed\n");
    unsubscribe(&k_id);
    printf("Keyboard unsubscribed\n");
    return 0;
    */
}
