/* Steven-style function definitions
 * CSE109 Fall 2021
 * ID: mhd224
 * Last name: Delen
 * First name: Muhammad
 * gitHub ID: mhd224 
 */
#include "syscalls.h"

int Unlink(const char* fileName){
	int val;
	if(( val = unlink(fileName)) == -1) {
		fprintf(stderr, "unlink error (%d): %s\n", errno, strerror(errno));
		exit(errno);
	}
	else return val;
}

/** wrapper for malloc
 *  numBytes    size_t
 */                                                                                                                                                           void* Malloc(size_t numBytes){
    void *ptr = NULL;
    if((ptr = malloc(numBytes)) == NULL){
        fprintf(stderr, "malloc error (%d): %s\n", errno, strerror(errno));
        exit(errno);
    }
    return ptr;
}

/** wrapper for calloc
 *  numBytes    size_t
 */
void* Calloc(size_t numObjects, size_t sizeOfObject){
    void *ptr = NULL;
    if((ptr = calloc(numObjects, sizeOfObject)) == NULL){
        fprintf(stderr, "calloc error (%d): %s\n", errno, strerror(errno));
        exit(errno);
    }
    return ptr;
}


/** wrapper for fopen
 *  const char *path
 *  const char *mode)
 */
FILE* Fopen(const char *path, const char *mode){
    FILE *fip = NULL;
    if((fip = fopen(path, mode)) == NULL) {
        fprintf(stderr, "Unable to open %s with mode %c - No such file or directory", path, *mode );
        exit(errno);
    }
    return fip;
}
/**wrapper for write
 *  *  void *buffer  (read from)
 *   *  size_t buffSize
 *    *  size_t numBuffers
 *     *  FILE *fp
 *      */
size_t Fwrite(const void *buffer, size_t buffSize, size_t numBuffers, FILE *fp){
    size_t bytesRead = 0;
	bytesRead = fwrite(buffer, buffSize, numBuffers, fp);
    if (ferror(fp) ) {    //there is error
    	fprintf(stderr, "fwrite error (%d): %s\n", errno, strerror(errno));
	    exit(errno);
    }
    return bytesRead;
}
ssize_t Write(int pfd, const void *buffer, size_t nbytes) {
  ssize_t numBytes;
  if ((numBytes = write(pfd, buffer, nbytes)) == -1) {
    fprintf(stderr, "Write error %d - %s", errno, strerror(errno));
    exit(errno);
  }
  return numBytes;
}

ssize_t Read(int pfd, void *buffer, size_t nbytes) {
  ssize_t numBytes;
  if ((numBytes = read(pfd, buffer, nbytes)) == -1) {
    fprintf(stderr, "Read error %d - %s", errno, strerror(errno));
    exit(errno);
  }
  return numBytes;
}


/** wrapper for Fclose
 *  File *fp
 */
void Fclose(FILE *fp){
    if(fclose(fp) != 0){ //error
        fprintf(stderr, "fclose error (%d): %s\n", errno, strerror(errno));
        exit(errno);
    }
}          

/**wrapper for Fread
 * void *buffer  (read into)
 * size_t buffSize
 * size_t numBuffers
 * FILE *fp
 **/
size_t Fread(void *buffer, size_t buffSize, size_t numBuffers, FILE *fp) {
    size_t bytesRead = 0;
	bytesRead = fread(buffer, buffSize, numBuffers, fp);
    if (!feof(fp) && ferror(fp)){ //EOF not set AND there is error
    	fprintf(stderr, "fread error (%d): %s\n", errno, strerror(errno));
	    exit(errno);
    }
    return bytesRead;
}
