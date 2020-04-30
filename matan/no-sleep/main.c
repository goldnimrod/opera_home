#include <stdio.h>
#include <sys/inotify.h>
#include <stdlib.h>
#include <unistd.h>

const char* SLEEP_PATH = "/usr/bin/sleep";

int main() {
    /**
     * This code watches the sleep binary and prints a message when someone executes
     * (or even touch) it.
     * @return EXIT_FAILURE on failure (exit success can be implemented with a signal handler, but it's not really
     * needed as the OS closes the inotify_fd on exit)
     */
    int inotify_fd;
    struct inotify_event buf;

    inotify_fd = inotify_init();
    if (-1 == inotify_fd) {
        printf("ERROR: Inotify failed to init\n");
        return EXIT_FAILURE;
    }

    // We basically tell this inofity_fd to write an event if there has been access to the SLEEP_PATH
    if (-1 == inotify_add_watch(inotify_fd, SLEEP_PATH, IN_ACCESS)) {
        printf("ERROR: Inotify add event failed\n");
        close(inotify_fd);
        return EXIT_FAILURE;
    }
    printf("DEBUG: waiting for something to happen\n");

    // read() is a blocking call so until there's something new to read - aka a new event from inotify
    while (-1 != read(inotify_fd, &buf, sizeof(buf))) {
        printf("Life is what happens when you are not watching\n"
               "so tonight, we are not gonna sleep!!!\n");
    }
    printf("ERROR: read failed\n");
    close(inotify_fd);
    return EXIT_FAILURE;
}
