#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int sockfd, portno, ret;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[1024];
	FILE *fptr, *fp;

	if (argc < 3) {
		printf("usage %s hostname port\n", argv[0]);
		return -EIO;
	}

	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0) {
		printf("Error opening socket\n");
		return -EAGAIN;
	}

	server = gethostbyname(argv[1]);

	if (server == NULL) {
		printf("No such host\n");
		return -EAGAIN;
	}

	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
	serv_addr.sin_port = htons(portno);

	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		printf("Conection failed.\n");
		return -EPERM;
	}

	fptr = fopen("data/sample.txt", "r");
	fp = fopen("output.txt", "w");

	if (fptr == NULL) {
		printf("The file is not opened.");
		return -ENOENT;
	}

	bzero(buffer, 1024);
	fgets(buffer, 1024, fptr);

	while (strlen(buffer)) {
		ret = write(sockfd, buffer, strlen(buffer));

		if (ret < 0) {
			printf("Error on Writing\n");
			return -EPERM;
		}

		bzero(buffer, 1024);
		ret = read(sockfd, buffer, 1024);

		if (ret < 0) {
			printf("Error on reading\n");
			return -EPERM;
		}

		printf("Server: %s\n", buffer);
		fputs(buffer, fp);
		fseek(fp, 0, SEEK_END);

		bzero(buffer, 1024);
		fgets(buffer, 1024, fptr);
	}

	fclose(fptr);
	fclose(fp);
	close(sockfd);

	return 0;
}
