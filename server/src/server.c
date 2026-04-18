#include <netinet/in.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

void *handler(void *sock)
{
	int newsock = *(int *)sock, ret;
	char buffer[1024];

	free(sock);

	while (1) {
		bzero(buffer, 1024);
		ret = read(newsock, buffer, 1024);

		if (ret < 0) {
			printf("Error on reading\n");
			return NULL;
		}

		printf("Client: %s\n", buffer);

		if (!strlen(buffer))
			break;

		for (int i = 0; buffer[i] != '\0'; i++) {
			if(buffer[i] >= 'a' && buffer[i] <= 'z') {
				buffer[i] = buffer[i] - 32;
			}
		}

		ret = write(newsock, buffer, strlen(buffer));

		if (ret < 0) {
			printf("Error on Writing\n");
			return NULL;
		}
	}

	close(newsock);

	return NULL;
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Port No. is not provided, program is terminated\n");
		return -EIO;
	}

	int sockfd, newsockfd, portno;
	int *ptr;
	struct sockaddr_in serv_addr, cli_addr;
	socklen_t clilen;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0) {
		printf("Error opening socket\n");
		return -EAGAIN;
	}

	bzero((char *)&serv_addr, sizeof(serv_addr));

	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		printf("Binding failed.\n");
		return -EPERM;
	}

	listen(sockfd, 5);

	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);

	if (newsockfd < 0) {
		printf("Error on accept\n");
		return -EPERM;
	}

	while (newsockfd) {
		pthread_t t;

		ptr = malloc(sizeof(int));
		*ptr = newsockfd;

		pthread_create(&t, NULL, handler, (void *)ptr);

		newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);

		if (newsockfd < 0) {
			printf("Error on accept\n");
			return -EPERM;
		}
	}

	close(sockfd);

	return 0;
}
