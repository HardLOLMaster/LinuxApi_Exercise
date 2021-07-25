/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cp_holes.c
 * Author: hlam
 *
 * Created on July 25, 2021, 12:09 PM
 */

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/*
 * 
 */
int main(int argc, char** argv) {
    int openflags;
    char* fileName;
    if (argc == 2) {
        openflags = O_RDWR | O_CREAT | O_TRUNC;
        fileName = argv[1];
    } else {
        fprintf(stderr, "Invalid arguments\n");
        return (EXIT_FAILURE);
    }
    ssize_t fd = open(fileName, openflags,
            S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
            S_IROTH | S_IWOTH); /* rw-rw-rw- */
    if (fd == -1) {
        fprintf(stderr, "Can't open file");
        return (EXIT_FAILURE);
    }
    char buf[10] = {"ABCDE12345"};

    ssize_t numWritten;
    if ((numWritten = write(fd, buf, sizeof buf)) < 0) {
        fprintf(stderr, "Write error");
        return (EXIT_FAILURE);
    }

    if (lseek(fd, 100, SEEK_CUR) == -1) {
        fprintf(stderr, "lseek error");
        return (EXIT_FAILURE);
    }

    if ((numWritten = write(fd, buf, sizeof buf)) < 0) {
        fprintf(stderr, "Write error");
        return (EXIT_FAILURE);
    }
    
    if (close(fd)) {
        fprintf(stderr, "Can't close file");
        return (EXIT_FAILURE);
    }

    return (EXIT_SUCCESS);
}

