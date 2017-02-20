#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define RCVBUFFERSIZE 32

void diewitherror(char *errormssg)
{
	perror(errormssg);
	exit(1);
} /* error handling function */

int main(int ac, char *av[])
{
	int sock;
	struct sockaddr_in echoServAddr;
	unsigned short echoServPort;
	char *servIP;
	char *echoString;
	char echoBuffer[RCVBUFFERSIZE];
	unsigned int echoStringLen;
	int bytesRcvd, totalBytesRcvd;

	if ((ac < 3) || (ac > 4))	/* test correct # of ag */
	{
		printf("Usage: %s <Server IP> <Echo Word> [<Echo Port>]\n", av[0]);
		exit(1);
	}
	servIP = av[1];			/* 1nd arg; serv IP address (dotted) */
	echoString = av[2];		/* 2nd arg; string to echo */
	if (ac == 4)
		echoServPort = atoi(av[3]); /*use given port, if any */
	else
		echoServPort = 7; /* 7 the port for echo service */

	/* Create a reliable, stream socket using TCP */
	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		diewitherror("socket() failed");

	/* Construct the server address structure */
	memset(&echoServAddr, 0 , sizeof(echoServAddr));	/* zero out structure */
	echoServAddr.sin_family = AF_INET;					/*internet addr fam */
	echoServAddr.sin_addr.s_addr = inet_addr(servIP);	/* server ip address */
	echoServAddr.sin_port = htons(echoServPort);		/* server port */

	/* Establish connection to the server */
	if ((connect(sock, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr))) < 0)
		diewitherror("connect() failed");

	echoStringLen = strlen(echoString);

	/* Send the string to the server */
	if (send (sock, echoString, echoStringLen, 0) != echoStringLen)
		diewitherror("send() sent a different number of bytes that expected!");

	/* recieve the same string back from the server */
	totalBytesRcvd = 0;
	printf("recieved: ");
	while (totalBytesRcvd < echoStringLen)
	{
		/* recieve up to the buffersize (-1 -> null) */
		if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFFERSIZE - 1, 0)) <= 0)
			diewitherror("recv() failed or connection closed prematurely");
		totalBytesRcvd += bytesRcvd;	/*keep tally of total bytes */
		echoBuffer[bytesRcvd] = 0;		/*terminate string */
		printf(echoBuffer);				/* print echo buffer */
	}

	printf("\n"); /*print a final linefeed */
	close(sock);
	exit(0);
}
