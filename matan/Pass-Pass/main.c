#include "main.h"

int get_terminal_width() {
    /**
     * Returns the width in columns of the terminal the code will print to
     * Note: this doesn't work while debugging in my IDE (Clion)
     * - so there is a commented out line in the main for these cases
     */
    struct winsize window;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
    return window.ws_col;
}

proc_t get_title_struct() {
    /**
     * Creates a proc_t struct that represents the table title, to then use print_proc on it
     * @return proc_t title struct
     */
    proc_t title_struct;

    title_struct.comm = "NAME";
    title_struct.pid = "PID";
    title_struct.path = "PATH";
    title_struct.cmd = "CMD";
    return title_struct;
}

void print_field(field_t field, int width) {
    /**
     * Formats and prints a field on proc data
     *
     * @param field [in] the field_t struct that holds data on the field to print
     * @param width [in] integer that contains the size of the terminal in columns
     */
    int size;
    char format[FIELD_SIZE_MAX] = {};

    // Size is the number of columns in the terminal allocated to the print of this field
    size = (int)(width * field.portion);

    if (TRUE == field.left_align) {
        // Eg. for field width 5, format will be "%-5.5s"
        // i.e. 'print a left-aligned string, padded to reach 5 and trimmed if longer than 5
        sprintf(format, "%%-%d.%ds ", size, size);
    } else {
        // Eg. for field width 5, format will be "%5.5s"
        // i.e. 'print a right-aligned string, padded to reach 5 and trimmed if longer than 5
        sprintf(format, "%%%d.%ds ", size, size);
    }
    printf(format, field.value);
}

void print_proc(proc_t *proc, int width) {
    /**
     * Prints a proc data nicely
     * Does this by hard-coding properties into the arrays, and creating field_t structs accordingly
     * Field_t structs are then printed by print_field
     */
    field_t arr[FIELDS_NUM];
    char* value_arr[FIELDS_NUM] = {proc->comm, proc->pid, proc->path, proc->cmd};

    for (int i = 0; i < FIELDS_NUM; ++i) {
        arr[i].portion = PORTION_ARR[i];
        arr[i].left_align = LEFT_ALIGN_ARR[i];
        arr[i].value = value_arr[i];

        print_field(arr[i], width);
    }
    printf("\n");
}

proc_t *malloc_proc() {
    /**
     * Mallocs a proc_t struct and the related strings
     * Size of each field is defined by FIELD_SIZE_MAX
     *
     * @return proc_t empty struct
     */
    proc_t *proc = (proc_t*)malloc(sizeof(proc_t));

    proc->comm = (char*)malloc(FIELD_SIZE_MAX);
    proc->pid = (char*)malloc(FIELD_SIZE_MAX);
    proc->path = (char*)malloc(FIELD_SIZE_MAX);
    proc->cmd = (char*)malloc(FIELD_SIZE_MAX);

    memset(proc->comm, 0, FIELD_SIZE_MAX);
    memset(proc->pid, 0, FIELD_SIZE_MAX);
    memset(proc->path, 0, FIELD_SIZE_MAX);
    memset(proc->cmd, 0, FIELD_SIZE_MAX);

    if (NULL == proc | NULL == proc->comm || NULL == proc->pid || NULL == proc->path || NULL == proc->cmd) {
        return NULL;
    }
    return proc;
}

void free_proc(proc_t *proc) {
    /**
     * Frees a proc struct and the related string
     */
    free(proc->comm);
    free(proc->pid);
    free(proc->path);
    free(proc->cmd);
    free(proc);
}

int readat(int dir_fd, char *pathname, char *buf, size_t maxsize) {
    /**
     * Reads maxsize chars from a file stream in a dir into char* buf
     *
     * @param dir_fd [in] the fd of the dir that the file is within
     * @param pathname [in] the name of the file within the dir
     * @param buf [in/out] the buffer that the read data will be written to
     * @param maxsize [in] the maximum number of chars to be read
     *
     * @return EXIT_SUCCESS on success, EXIT_FAILURE otherwise
     */
    FILE *stream;
    char c;
    char read[maxsize];
    int readsize;
    int ret = EXIT_FAILURE;
    int file_fd;

    file_fd = openat(dir_fd, pathname, O_RDONLY);
    if (-1 == file_fd) {
        return ret;
    }
    stream = fdopen(file_fd, "r");
    if (NULL == stream) {
        close(file_fd);
        return ret;
    }
    // Clear read from last run's data
    memset(read, 0, maxsize);

    // For loop that reads chars from the file stream
    for (readsize = 0; readsize < maxsize && EOF != (c = fgetc(stream)) && '\n' != c; ++readsize) {
        // In proc, sometimes 0x0a marks the end of the readable part of the file
        read[readsize] = c;
    }
    // fgetc() returns EOF for EOF and for failures, so return success only if it's actually an EOF
    if (TRUE == feof(stream) || '\n' == c) {
        strcpy(buf, read);
        ret = EXIT_SUCCESS;
    }
    fclose(stream);
    return ret;
}

int main() {
    /**
     * Emulates the behavior of PS
     * Loops on all dirs in /proc that represents running procs
     * Gets proc data for each proc by reading "/exe", "/cmdline", "/comm"
     * Eventually prints the data nicely, similarly to ps, using side functions
     *
     * @return EXIT_SUCCESS in general
     */
    DIR *proc_p;
    struct dirent *dir_in_proc;
    char *pid;
    proc_t *proc_struct;
    proc_t title_struct;
    int dir_fd;
    int proc_fd;
    int ret;
    int terminal_width;

    terminal_width = get_terminal_width();
    //terminal_width = 50; // This line exist because in CLion, the above returns 0. Should be a comment except in debug

    // Print the title of the table
    title_struct = get_title_struct();
    print_proc(&title_struct, terminal_width);

    // Open /proc
    proc_p = opendir(PROC);
    proc_fd = dirfd(proc_p);

    // Loops on all files in /proc
    while (NULL != (dir_in_proc = readdir(proc_p))) {
        // Continue if file isn't a directory
        if (DT_DIR != dir_in_proc->d_type) {
            continue;
        }
        // Continue if local dirname is not digits (atoi returns 0 if it cannot convert, and there is no 0 pid in linux)
        pid = dir_in_proc->d_name;
        if (0 == atoi(pid)) {
            continue;
        }
        // Continue if dir failed to open
        dir_fd = openat(proc_fd, pid, O_RDONLY);
        if (-1 == dir_fd) {
            continue;
        }
        // malloc a proc struct for that proc dir, continue if failed
        proc_struct = malloc_proc();
        if (NULL == proc_struct) {
            close(dir_fd);
            continue;
        }
        strcpy(proc_struct->pid, pid);

        ret = readat(dir_fd, "comm", proc_struct->comm, FIELD_SIZE_MAX);
        // If the read failed, don't crash the code or even skip the proc, but do print the error message in that field
        if (EXIT_FAILURE == ret) {
            strcpy(proc_struct->comm, "ERROR in comm read");
        }
        ret = readat(dir_fd, "cmdline", proc_struct->cmd, FIELD_SIZE_MAX);
        // If the read failed, don't crash the code or even skip the proc, but do print the error message in that field
        if (EXIT_FAILURE == ret) {
            strcpy(proc_struct->cmd, "ERROR in cmdline read");
        }
        ret = readlinkat(dir_fd, "exe", proc_struct->path, FIELD_SIZE_MAX);
        // If this failed, don't crash the code or even skip the proc, but do print the error message in that field
        if (-1 == ret) {
            strcpy(proc_struct->path, "ERROR in exe readlink");
        }

        print_proc(proc_struct, terminal_width);
        free_proc(proc_struct);
        close(dir_fd);
    }
    closedir(proc_p);
    return EXIT_SUCCESS;
}
