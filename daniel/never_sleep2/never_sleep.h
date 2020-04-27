#ifndef NEVER_SLEEP_H
#define NEVER_SLEEP_H

#include <limits.h>
#include <stdlib.h>

#define SLEEP_NAME_STRING "(sleep)"
#define MAX_PROC_NAME 600
#define MAX_PROC_PATH_NAME 500
#define STAT_PATH_STRING "/proc/%d/stat"

/**
 * the function gets a pid and returns whether the process is a sleep process.
 * @param pid the process id.
 * @return 0 if the strings are equal, otherwise a different number.`
 */
int isSleep(pid_t pid);

#endif //NEVER_SLEEP_H
