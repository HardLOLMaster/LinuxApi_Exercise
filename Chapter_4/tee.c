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
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#define MAX_LENGHT 20

/*
 *
 */
int main(int argc, char** argv) {
    int fd;
    char buf[MAX_LENGHT] = {};
    ssize_t numRead, numWritten;
    int openflags;
    char* fileName;
    if (argc == 2) {
        openflags = O_WRONLY | O_CREAT | O_TRUNC;
        fileName = argv[1];
    } else if (argc == 3) {
        if (strcmp(argv[1], "-a") == 0) {
            openflags = O_WRONLY | O_CREAT | O_APPEND;
            fileName = argv[2];
        } else {
            fprintf(stderr, "Invalid arguments\n");
            return (EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "Invalid arguments\n");
        return (EXIT_FAILURE);
    }

    fd = open(fileName, openflags,
            S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
            S_IROTH | S_IWOTH); /* rw-rw-rw- */
    if (fd == -1) {
        fprintf(stderr, "Can't open file");
        return (EXIT_FAILURE);
    }

    while ((numRead = read(STDIN_FILENO, buf, MAX_LENGHT)) > 0) {
        if ((numWritten = write(fd, buf, MAX_LENGHT)) < numRead) {
            fprintf(stderr, "Write error");
            return (EXIT_FAILURE);
        }
        memset(buf, 0, sizeof buf);
    }

    if (close(fd)) {
        fprintf(stderr, "Can't close file");
        return (EXIT_FAILURE);
    }

    return (EXIT_SUCCESS);
}