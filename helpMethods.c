
/* FtpDonwlaod & ftpWrite
 * CSE109 Fall 2021
 * ID: mhd224
 * Last name: Delen
 * First name: Muhammad
 * gitHub ID: mhd224 
 * */
#include "syscalls.h"
#include "helpMethods.h"

int ftpDownload(char *userid, char *password, char *server, char *pathname, char* fileName) {
	char str[128];                                               /* character string for setting curl settings, call values, or bail messages */
	CURLcode crc;                                                /* variable to hold CURL function return codes */
	CURL *cp = NULL;                                             /* pointer/handle to curl session/transfer */
	
	
	ftpFile_t FTPfile = { fileName, NULL };              /* declare and define an ftpFile_t object, you can change filename or make it a variable */

	curl_global_init(CURL_GLOBAL_ALL);                           /* 1 - initialize curl global state; setup and initialize underlying libraries */

	cp =  curl_easy_init();                                      /* 2 - initialize pointer/handle for curl session/transfer */

  if (cp) {                                                    /* check if curl handle creation was successful, and if so, proceed */
    sprintf(str, "%s:%s", userid, password);                   /* set string str to "<userid>:<password>" */

	curl_easy_setopt(cp, CURLOPT_USERPWD, str);                /* 3 - set username and password */

    sprintf(str, "sftp://%s/%s", server, pathname);            /* change string str to "sftp://<server>/<pathname>" */

	curl_easy_setopt(cp, CURLOPT_URL, str);                    /* 4 - set protocol, server, directory, and file */

	curl_easy_setopt(cp, CURLOPT_WRITEFUNCTION, ftpWrite);       /* 5 - declare our callback to be called when there's data to be written */

	curl_easy_setopt(cp, CURLOPT_WRITEDATA, &FTPfile);           /* 6 - set a pointer to our struct to pass to the callback */

	curl_easy_setopt(cp, CURLOPT_VERBOSE, 0L);                 /* switch on full protocol/debug output */

	crc =  curl_easy_perform(cp);                              /* 7 - perform the curl call and capture the return value */

	curl_easy_cleanup(cp);                                              /* 8 - cleanup local session/transfer */
 	if(FTPfile.stream != NULL){ 
		Fclose(FTPfile.stream);                                               /* 9 - close the local file */
	}
	curl_global_cleanup();                                     /* 10 - free and clean up associated global resources init call allocated */

  } else {                                                     /* bail in the unlikely event curl handle creation failed */
    fprintf(stderr, "Initialization of curl session/transfer handle was unsuccessful\n");
    exit(202);
  }

  return (int)crc;                                             /* return curl return code */
}


size_t ftpWrite(void *buffer, size_t size, size_t nmemb, void *stream) {
ftpFile_t *oFile = (ftpFile_t *)stream;
  if(!oFile->stream)
    oFile->stream = Fopen(oFile->filename, "w");  /* open file for writing */
  return Fwrite(buffer, size, nmemb, oFile->stream);
}

