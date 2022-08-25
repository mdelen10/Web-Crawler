#include "syscalls.h"

/* function prototype and typedef struct */
int ftpDownload(char *, char *, char *, char *, char* fileName);
size_t ftpWrite(void *, size_t, size_t, void *);

struct ftpfile {
  const char *filename;   /* name to store the file as */
  FILE *stream;           /* file pointer/handle */
};
typedef struct ftpfile ftpFile_t;
