#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <errno.h>

#define SLEEP_PATH "/usr/bin/sleep"

extern int errno;

void main() {
    int sleepFd = inotify_init();
    struct inotify_event event;
    int watch_value = inotify_add_watch(sleepFd, SLEEP_PATH, IN_OPEN);
    if (watch_value == -1) {
        perror("error while trying to open file - ");
        exit(errno);
    }
    while (1) {
        read(sleepFd, (void *) &event, sizeof(struct inotify_event));
        printf("Wake up sunshine!\n");
    }
}
