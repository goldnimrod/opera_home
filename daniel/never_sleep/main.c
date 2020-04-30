#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <errno.h>

#define SLEEP_PATH "/usr/bin/sleep"

extern int errno;

void main() {
    struct inotify_event event;
    int sleep_fd = inotify_init();
    if (sleep_fd == -1) {
        perror("error with trying to init the inotify object- ");
        exit(errno);
    }
    int watch_value = inotify_add_watch(sleep_fd, SLEEP_PATH, IN_OPEN);
    if (watch_value == -1) {
        perror("error while trying to open file - ");
        exit(errno);
    }
    while (1) {
        read(sleep_fd, (void *) &event, sizeof(struct inotify_event));
        printf("Wake up sunshine!\n");
    }
}
