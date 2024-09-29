/**
 * @file proj.c
 * @brief Main file of the project. Initializes interrupts and the main loop
 * @author T17_G1
 * @date 27/05/2024
 */

#include <lcom/lcf.h>
#include "shared.h"
#include "setup.h"
#include <interrupts/interrupts.h>

#define DEBUG
#include <auxiliary/debug.h>

/**
 * @brief LCF function
 * @param int argc : number of arguments passed to the function
 * @param char **argv : array of arguments passed to the function
 * @return int : 0 on success
 */
int main(int argc, char **argv) {
    lcf_set_language("EN-US");
    lcf_trace_calls("/home/lcom/labs/proj/trace.txt");

    if (lcf_start(argc, argv))
        return 1;

    lcf_cleanup();
    return 0;
}

/**
 * @brief Main loop of the project. Depending on which argument was provided, executes a certain function
 * @param int argc : number of arguments passed to the function
 * @param char **argv : array of arguments passed to the function
 * @return int : 0 on success
 */
int (proj_main_loop)(int argc, char **argv) {
    int (*setup)(int, char **);
    if (argc == 0 || !strcmp(argv[0], "ipc")) setup = ipc_setup;
    else if (!strcmp(argv[0], "debug-keyboard")) setup = keyboard_debug_setup;
    else if (!strcmp(argv[0], "proj")) setup = proj_setup;
    else if (!strcmp(argv[0], "penguin")) setup = penguin_setup;
    else if (!strcmp(argv[0], "rtc")) setup = rtc_test;
    else if (!strcmp(argv[0], "serial-port")) setup = serial_port;
    else if (!strcmp(argv[0], "windows")) setup = windows_setup;
    else if (!strcmp(argv[0], "ipc")) setup = ipc_setup;
    else {
        printf(
            "Invalid argument(s) provided. Available setups:\n"
                "\t./main penguin: Movable penguin\n"
                "\t./main debug-keyboard: prints key press/release info\n"
                "\t./main proj: Currently, just allows moving between directories through text mode\n"
                "\t./main rtc <args>: Used to test the Real Time Clock\n"
                "\t./main serial-port <args>: Used to test the Serial Port\n"
                "\t./main windows: Used to test moving rectangles\n"
                "\t./main [\"ipc\"]: Use windows created and manipulated by other processes\n"
        );
        return 1;
    }

    if (setup(argc-1, argv+1)) {
        fprintf(stderr, "Failed to setup program :(\n");
        prog_cleanup();
        return 1;
    }

    if (interrupts_run()) {
        prog_cleanup();
        return 1;
    }

    prog_cleanup();
    return 0;
}
