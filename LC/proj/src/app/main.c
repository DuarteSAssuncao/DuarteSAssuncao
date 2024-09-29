/**
 * @file main.c
 * @brief Prologue of the project. Obtains the home folder location and then executes "lcom_run proj"
 * @author T17_G1
 * @date 27/05/2024
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <app/ipc/middleman.h>
#include <unistd.h>
#include "shared.h"

#define DEBUG
#include <auxiliary/debug.h>

/**
 * @brief First function to be called
 * @param int argc : number of arguments passed to the function (including "./main")
 * @param char **argv : array of arguments passed to the function (the first one being "./main")
 * @return int : 0 on success
 */
int main(int argc, char **argv) {
    const char *homedir; // path to the home directory
    FILE *shared_file;

    TRY(homedir = getenv("HOME"),                   ==NULL, "return value is NULL", 1,);
    TRY(shared_file = fopen(SHARED_FILE, "w"),      ==NULL, strerror(errno), 1,);
    TRY(fputs(homedir, shared_file),                ==EOF, strerror(errno), 1,);
    TRY(fclose(shared_file),                        ==EOF, strerror(errno), 1,);

    char ** args = (char**) calloc(argc + 2, sizeof(*args));
    args[0] = "lcom_run", args[1] = "proj";
    memcpy(args + 2, argv + 1, argc * sizeof(*args));

    if (fork() > 0) {
        execvp(args[0], args);
        DEBUG_PERRORV("lcom_run failed");
        return 1;
    }

    if (argc != 1 && strcmp(argv[1], "ipc"))
        return 0;

    TRY(rakoon_middleman_init(),                    != 0, strerror(errno),1,);
    TRY(rakoon_middleman_start(),                   != 0, strerror(errno),1,);
    rakoon_middleman_cleanup();
    return 0;
}
