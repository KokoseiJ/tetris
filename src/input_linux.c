#include "input.h"
#include <linux/input.h>
#include <poll.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>

struct pollfd pfd[1];
TetrisKeyStatus status = {0, 0, 0, 0, 0, 0};


uint8_t input_init() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, 0, &term);
    pfd->fd = open("/dev/input/by-id/usb-ASUSTeK_Computer_Inc._N-KEY_Device-if02-event-kbd", O_RDONLY | O_NONBLOCK);
    if (pfd->fd == -1) return -1;
    
    pfd->events = POLLIN;
    return 0;
}


uint8_t input_cleanup() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ECHO;
    tcsetattr(STDIN_FILENO, 0, &term);
    return close(pfd->fd);
}


TetrisKeyStatus *input_status() {
    int ready;
    ssize_t num_read;
    struct input_event ievent;
    bool *target_key;

    while (true) {
        ready = poll(pfd, 1, 0);
        if (ready == -1) return NULL;
        if (!pfd->revents & POLLIN) break;
        //printf("POLLIN event detected\n");
        
        num_read = read(pfd->fd, &ievent, sizeof(struct input_event));
        if (num_read < 0) return NULL;
        //printf("%d bytes read\n", num_read);
        //printf("event type: %d code: %d value %d\n", ievent.type, ievent.code, ievent.value);
        if (ievent.type != EV_KEY) continue;
        switch (ievent.code) {
        case KEY_W:
            //printf("KEY_W\n");
            target_key = &status.d_up;
            break;
        case KEY_A:
            //printf("KEY_A\n");
            target_key = &status.d_left;
            break;
        case KEY_S:
            //printf("KEY_S\n");
            target_key = &status.d_down;
            break;
        case KEY_D:
            //printf("KEY_D\n");
            target_key = &status.d_right;
            break;
        case KEY_K:
            //printf("KEY_K\n");
            target_key = &status.r_left;
            break;
        case KEY_L:
            //printf("KEY_L\n");
            target_key = &status.r_right;
            break;
        default:
            target_key = NULL;
        }

        if (target_key != NULL) {
            *target_key = (!ievent.value ? 0 : 1);
            printf("key %d val %d ", ievent.code, ievent.value);
        }
    }
    return &status;
}
