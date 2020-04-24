//
// Created by matt on 24/04/2020.
//

#ifndef PASS_PASS_2_MAIN_H
#define PASS_PASS_2_MAIN_H

#include <ctype.h>
#include <dirent.h>
#include <fcntl.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <errno.h>

#define FIELDS_NUM 4
#define TRUE 1
#define FALSE 0
#define FIELD_SIZE_MAX 128

// These are the portions of the printout for each field
// They all sum to 1
const double NAME_PORTION = 0.2;
const double PID_PORTION = 0.1;
const double PATH_PORTION = 0.25;
const double CMD_PORTION = 1 - (NAME_PORTION + PID_PORTION + PATH_PORTION); // It's 0.5 but to be sure

// These are consts hard-coded with field properties to be used in print_field()
const double PORTION_ARR[FIELDS_NUM] = {NAME_PORTION, PID_PORTION, PATH_PORTION, CMD_PORTION};
const int LEFT_ALIGN_ARR[FIELDS_NUM] = {TRUE, FALSE, TRUE, TRUE};
const char *PROC = "/proc";

typedef struct _proc_t {
    char *comm;
    char *pid;
    char *path;
    char *cmd;
} proc_t;

typedef struct _field_t {
    double portion;
    int left_align;
    char *value;
} field_t;

#endif //PASS_PASS_2_MAIN_H
