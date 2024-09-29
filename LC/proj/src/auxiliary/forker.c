/**
 * @file forker.c
 * @brief Program used to create multiple instances of another program.
 * @author T17_G1
 * @date 02/06/2024
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

/**
 * @brief Main function. Creates forks one after the other
 * @param int argc : number of arguments passed to the function
 * @param char **argv : arguments passed to the function
 * @return int : 0 on success
 */
int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "%s: Usage: %s <times> <prog-path> [...args]\n", argv[0], argv[0]);
        return 1;
    }

    int times;
    if (sscanf(argv[1], "%d", &times) != 1) {
        fprintf(stderr, "%s: second argument must be a number\n", argv[0]);
        return 1;
    }

    for (int i = 0; i < times; ++i) {
        int pid = fork();
        if (pid == 0) {
            execvp(argv[2], argv + 2);
            fprintf(stderr, "%s: execvp(\"%s\", ...): %s\n", argv[0], argv[2], strerror(errno));
            return 1;
        } else if (pid < 0) {
            perror("fork");
            return 1;
        }
    }

    return 0;
}
