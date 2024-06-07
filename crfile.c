#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#if defined(__i386__) || defined(__x86_64__)
#define _GNU_SOURCE 1
#endif
#ifndef O_TMPFILE
#if defined(__alpha__)
#define __O_TMPFILE 0100000000
#elif defined(__parisc__) || defined(__hppa__)
#define __O_TMPFILE 0400000000
#elif defined(__sparc__) || defined(__sparc64__)
#define __O_TMPFILE 0x2000000
#else
#define O_TMPFILE 020000000
#endif
#endif
#include <unistd.h>
#include <fcntl.h>

/* Simple program to provide file creation utility. writes empty file. 255 character filename maximum. checks for existing filename */

int main(int argc, char **argv) {
	char *mcharstring = NULL; /*start argv to char * string */
	size_t arglen = 0;
	for (size_t i = 1; argv[i] != NULL; i++) {
		mcharstring = realloc(mcharstring, arglen += strlen(argv[i]) + 1);
		strcat(mcharstring, argv[i]);
		strcat(mcharstring, " "); }
		if (argc > 1) { mcharstring[arglen] = '\0'; } /*end argv to char * string */

	int fd;
	char charbuf [sizeof(char*[32])]; /* 255 characters*/
	
	if (argc <= 1) { perror("not interactive, add arguments"); fflush(stdin); free(mcharstring); exit(1); }
	
	else if (argc > 1) { sscanf(mcharstring, "%255s", charbuf);
		if(access(&charbuf, F_OK && R_OK) == 0) { perror("file already exists, quitting"); fflush(stdin); free(mcharstring); exit(1); }
		else if((fd=open(&charbuf, O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU | S_IRWXG | S_IRWXO)) < 0 ) {
			perror("crfile() failure"); fflush(stdin); free(mcharstring); exit(1); }
			write(fd, "\0", 0); if(close(fd)) { perror(NULL); fflush(stdin); free(mcharstring); exit(1); } goto cleanup; }

	else
	cleanup:;		 
	fflush(stdin);
	free(mcharstring);
	return(0);
}
