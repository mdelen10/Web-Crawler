/* Steven-style function header
 * CSE109 Fall 2021
 * ID: mhd224
 * Last name: Delen
 * First name: Muhammad
 * gitHub ID: mhd224 
 */

#ifndef SYSCALLS_H
#define SYSCALLS_H


#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <string.h>      /* for strerror */
#include <curl/curl.h>   /* for curl, baby! */
#include <termios.h>

int Unlink(const char *filename);
void Fclose(FILE *fp);
FILE* Fopen(const char *path, const char *mode);
size_t Fwrite(const void *buffer, size_t buffSize, size_t numBuffers, FILE *fp);
void* Malloc(size_t numBytes);
void* Calloc(size_t numObjects, size_t sizeOfObject);
ssize_t Write(int, const void *, size_t);
ssize_t Read(int, void *, size_t);
size_t Fread(void *buffer, size_t buffSize, size_t numBuffers, FILE *fp);
#endif
