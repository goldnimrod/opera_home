#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "never_sleep.h"


int is_sleep(pid_t pid) {
    char name[MAX_PROC_NAME];
    char stat_file_name[MAX_PROC_PATH_NAME];
    sprintf(stat_file_name, STAT_PATH_STRING, pid);
    FILE *statFile = fopen(stat_file_name, "r");
    if (statFile != NULL) {
        fscanf(statFile, "%*s %s", name);
    }
    return !strcmp(name, SLEEP_NAME_STRING);
}

/**
 * the function goes over the proc directory
 * infinitely until finding a sleep process.
 */
int main() {
    DIR *directory;
    struct dirent *file;
    pid_t pid;

    //infinite loop.
    while (1) {
        directory = opendir("/proc");
        if (directory) {
            file = readdir(directory);
            while (file != NULL) {
                pid = atoi(file->d_name);
                if (pid) {
                    if (is_sleep(pid)) {
                        printf("Wake up honey!!!\n");
                    }
                }
                file = readdir(directory);
            }
        } else {
            perror("couldn't open /proc dir.");
            exit(errno);
        }
        closedir(directory);
    }
}
