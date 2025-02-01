#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_COUNT 20
char *buffer[MAX_COUNT];

int main(int argc, char *argv[]) {
	int rdfd = open(argv[1], O_RDONLY);
	
	if (rdfd == -1) {
		perror("Unable to open file");
		exit(EXIT_FAILURE);
	}

	int wrfd = open(argv[2], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

	if (wrfd == -1) {
		perror("Unable to create file");
		exit(EXIT_FAILURE);
	}

	ssize_t br;

	while((br = read(rdfd, buffer, MAX_COUNT)) > 0) {
		buffer[br] = '\0';
		ssize_t bw = write(wrfd, buffer, MAX_COUNT);

		if (bw == -1) {
			perror("Cannot write to the file!");
			exit(EXIT_FAILURE);
		}
	}

	if (br == -1) {
		perror("Cannot read file");
		exit(EXIT_FAILURE);
	}

	close(rdfd);
	close(wrfd);
	exit(EXIT_SUCCESS);
}
