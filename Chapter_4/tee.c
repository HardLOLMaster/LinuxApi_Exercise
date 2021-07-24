/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: hlam
 *
 * Created on July 24, 2021, 9:40 PM
 */

#include <sys/stat.h>
#include <stdarg.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

/*
 *
 */
int main(int argc, char** argv) {
    size_t len;
    off_t offset;
    int fd, ap, j;
    char *buf;
    size_t numRead, numWritten;
    if (!(argc > 1)) {
        fprintf(stderr, "Arguments empty");
        return (EXIT_FAILURE);
    }
    char* fileName = argv[1];
    fd = open(fileName, O_RDWR | O_CREAT,
            S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
            S_IROTH | S_IWOTH); /* rw-rw-rw- */
    if (fd == -1) {
        fprintf(stderr, "Can't open file");
        return (EXIT_FAILURE);
    }
    fprintf(stdout, "File opened\n");

    if (close(fd)) {
        fprintf(stderr, "Can't close file");
        return (EXIT_FAILURE);
    }
    fprintf(stdout, "File closed");

    return (EXIT_SUCCESS);
}