#include <stdio.h>
#include <string.h>
#include "headers/dbHandler.h"
#include <unistd.h>

void *connectionHandler(void *sockptr) {

	int sock = *(int *)sockptr;

	int maxMessageLength = 10000;
	int bufferSize = maxMessageLength + 1;

	char *readBuffer[bufferSize];
	
	int read_size;
	while( (read_size = read(sock , readBuffer , bufferSize)) > 0) {
		
 		if (read_size > maxMessageLength) {

			char message[] = "Max size is 10.000 characters!\n";
			write(sock, message, strlen(message));
			close(sock);
		}

		char key[5];
		printf("Received %d bytes\n", read_size);
		writeDB(&key, readBuffer);
		
		char url[24];
		sprintf(url, "http://catbin.xyz/%s\n", key);

		// First write url then write key
		write(sock, url, strlen(url));
		close(sock);

	}

	return NULL;

}