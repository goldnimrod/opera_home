#include "main.h"

int read_at_to(int dir_fd, const char *file_name, char *buf) {
    fd = openat(dir_fd, file_name, O_RDONLY);
    result = read(fd, buf);
    if (-1 == result) {
        close(fd)

    }
}

proc_t *get_proc_data(char* proc_dir_path) {
    DIR *p_dir = opendir(proc_dir_path);
    char *dir_name;
    char *file_name;
    int counter = 0;
    int dir_fd;
    proc_t proc;
    struct dirent *file_in_dir_struct;

    dir_fd = dirfd(p_dir);
    if (-1 == dir_fd) {
        goto failure;
    }
    dir_name = basename(proc_dir_path);

    // Check if all chars are digits, and return with failure if not
    while (isdigit(dir_name[counter])) {
        ++counter;
    }
    if ((sizeof(dir_name) / sizeof(dir_name[0])) != counter) {
        goto failure;
    } else {
        proc.pid = atoi(dir_name);
    }

    while (NULL != (file_in_dir_struct = readdir(p_dir)))
    {
        file_name = file_in_dir_struct->d_name;

        if ("comm" == file_name) {
            if (-1 == read_at_to(dir_fd, file_name, proc.name)) {
                goto failure;
            }
        } else if ("cmdline" == file_name) {
            if (-1 == read_at_to(dir_fd, file_name, proc.cmd_line)) {
                goto failure;
            }
        } else if ("exe" == file_name) {
            if (-1 == readlinkat(dir_fd, file_name, proc.binary_path, NAME_MAX)) {
                goto failure;
            }
        }
    }

    return &proc;

failure:
    closedir(p_dir);
    return EXIT_FAILURE;
}

int main() { //TODO
    printf("Hello, World!\n");
    return 0;
}
