#include <app/ipc/api.h>
#include <stdio.h>

#define DEBUG
#include <auxiliary/debug.h>

/**
 * argv[0] = 0 to receive, non-zero to send
 * argv[1] = full path of the origin/destination file
 */
int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <0 : receive, 1 : send> <fullpath>\n", argv[0]);
        return 1;
    }

    win_t *win = win_create(NULL);
    if (win == NULL) {
        perror("win_create");
        return 1;
    }

    int x;
    if (sscanf(argv[1], "%d", &x) != 1) {
        fprintf(stderr, "%s: First argument must be numeric\n", argv[0]);
        return 1;
    }

    if (x == 0) {
        if (receive_file_through_serial_port(win, argv[2])) {
            perror("receive_file_through_serial_port");
            return 1;
        }
    } else {
        if (send_file_through_serial_port(win, argv[2])) {
            perror("send_file_through_serial_port");
            return 1;
        }
    }

    win_close(win);
    return 0;
}
