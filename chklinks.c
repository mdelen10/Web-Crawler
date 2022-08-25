/* Main file
 * CSE109 Fall 2021
 * ID: mhd224
 * Last name: Delen
 * First name: Muhammad
 * gitHub ID: mhd224 
 * */
#include "syscalls.h"
#include "helpMethods.h"

void parseargs(int argc);
void getPass(char *);
int getch();
void readFile(FILE* fp, char*, char*, int* counter);
void findDeadLinks(char *, char* , char *, char*, int*);

int main(int argc, char** argv){
	parseargs(argc); //parseargs
	char* userid = argv[1];
	char* server = argv[2];
	char* pathName = argv[3];
	char pw[25];
	getPass(pw);  //get password
	int counter = 0;
	findDeadLinks(userid, pw, server, pathName, &counter); //recursive function called by readFile
}
void findDeadLinks(char * userid, char* pw, char * server, char* pathName, int* counter){
    char fileName[48]; //file
    const char *prefix = "/tmp/file.";
	int pid = getpid(); 
    snprintf(fileName, 48, "%s%d.%d", prefix, pid, (*counter)++); //increment counter after making fileName
    //printf("%s\n",fileName);

    int rc = ftpDownload(userid, pw,  server, pathName, fileName); //5th arg should be string name of file
    if(rc == 0){  //successful curl
        FILE *fp = Fopen(fileName, "r");
        readFile(fp, userid, pw, counter);
    }
	pathName++; //ref prints don't include pathName inital forwardslah

	if (rc)                                                    //transfer was unsuccessful 
        fprintf(stderr, "%s (%d) - %s on %s\n", curl_easy_strerror(rc), rc, pathName, server);
	else { 
		//printf("deleting file  %s.... %s %s\n", fileName, server, pathName );
		Unlink(fileName); //unlink file name from temp
	}
}

void parseargs(int argc){
	switch (argc) {
		case 4:
			break;
		default:
			fprintf(stderr, "Expecting 4 arguments to be passed\n");
			fprintf(stdout, "\nUsage: curlFTP <userid> <password> <server> <fully-qualified filename>\n\n");
			exit(201);
			break; 
	} 
}

void readFile(FILE* fp, char* userid, char* pw, int* counter){
	char buffer[256]; 	//holds tag <	
	char serverName[256];
	char pathName[256];
	char* serverNameStart;
	char* serverNameEnd;
	char* pathNameEnd;
	while(fscanf(fp, "%[^<]", buffer ) != EOF ){ //buffer gets everything before <
		fscanf(fp, "%[^>]", buffer); 
		if(buffer[1] == 'a'){  //only get href linkhttpString = strstr(buffer, "http");
			char* httpString = strstr(buffer, "http"); //gets pointer for "http" or returns null
			char* serverDelim = strstr(buffer, "://"); //gets pointer for "://" or returns null
			if(httpString == NULL) 		//no "http"
				fprintf(stderr, "No \"http[s]\" found in URL (202) -  %s\n",   strstr(buffer, "href"));
			else if(serverDelim == NULL)  //no "://" 
				fprintf(stderr, "No \"://\" found in URL (203) -  %s\n", strstr(buffer, "href") );
			else{  //good href
				char* goodLink = strstr(buffer, "\""); //get up to the beginning of path (first quote)
				goodLink++; //increment past quote
                
				if (strncmp(goodLink, "https://", 8) == 0)
					serverNameStart = goodLink + 8; //increment goodLink pointer  8
				else if (strncmp(goodLink, "http://", 7) == 0)		
					serverNameStart = goodLink + 7;  //increment goodLink pointer 7
				else{
					fprintf(stderr, "No \"://\" found in URL (203) -  %s\n", strstr(buffer, "href") );
				} 
				serverNameEnd = strchr(serverNameStart, '/');  /* point to the first '/' */
				*serverNameEnd = '\0';  /* replace that '/' with a '\0' so strcpy stops copying there */
				strcpy(serverName, serverNameStart); /* copy the server name into serverName variable */

				*serverNameEnd = '/'; /* point to the character just after the '/' following the server name */
				pathNameEnd = strchr(serverNameEnd, '\"');  /* point to the final quote */
				*pathNameEnd = '\0';  /*replace final quote with termiantor"*/
				strcpy(pathName, serverNameEnd);  /* copy from serverNameEnd to the '\0' at the end of the string in to the filename variable */
				findDeadLinks(userid, pw, serverName, pathName, counter);
            }	
		} 
	}
}

void getPass(char* password){
	char ch;
    printf("Enter password: ");
    int i = 0;
    while( (ch = getch()) != '\n'){
        password[i] = ch;
        printf("*");
        i++;
    }
	password[i] = '\0';  //add null terminator
	printf("\n");
    //printf("\nYou have entered %s as password.\n", password);
}
int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
