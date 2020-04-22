//
// Created by matt on 22/04/2020.
//

#ifndef PASS_PASS_MAIN_H
#define PASS_PASS_MAIN_H
    #include <ctype.h>
    #include <dirent.h>
    #include <fcntl.h>
    #include <libgen.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <sys/types.h>
    #include <unistd.h>

    typedef struct {
        char *name;
        int pid;
        char *binary_path;
        char *cmd_line;
    } proc_t;
#endif //PASS_PASS_MAIN_H
