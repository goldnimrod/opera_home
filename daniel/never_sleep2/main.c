#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "never_sleep.h"


int isSleep(pid_t pid) {
    char name[MAX_PROC_NAME];
    char statFileName[MAX_PROC_PATH_NAME];
    sprintf(statFileName, STAT_PATH_STRING, pid);
    FILE *statFile = fopen(statFileName, "r");
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
                if (atoi(file->d_name)) {
                    pid = atoi(file->d_name);
                    if (isSleep(pid)) {
                        printf("Wake up honey!!!\n");
                    }
                }
                file = readdir(directory);
            }
        }
        closedir(directory);
    }
}
