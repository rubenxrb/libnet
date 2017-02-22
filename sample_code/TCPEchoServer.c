#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXPENDING 5		/* maximum outstanding connection requests */
#define RCVBUFSIZE 32

void diewitherror(char *errormssg)
{
	perror(errormssg);
	exit(1);
} /* error handling function */

void handleTCPClient(int clntSocket)
{
	char echoBuffer[RCVBUFSIZE];	/* Buffer for echo string */
	int recvMsgSize;				/* Size of received message */

	/* Receive message from client */
	if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
		diewitherror("recv() failed");

	/* Send received string and receive again until end of transmission */
	while (recvMsgSize > 0) /* zero indicates end of transmission */
	{
		/* Echo message back to client */
		if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
			diewitherror("send() failed");

		/* See if there is more data to receive */
		if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
			diewitherror("recv() failed");
	}

	close(clntSocket);		/* Close client socket */
}	/* TCP client hadling function */

int main(int ac, char *av[])
{
	int servSock;		/* server socket descriptor */
	int clntSock;		/* client socket descriptor */
	struct sockaddr_in echoServAddr;	/* server socket detailed abstraction */
	struct sockaddr_in echoClntAddr;	/* client socket detailed abstraction */
	unsigned short echoServPort;	/* server socket portnumber */
	unsigned int clntLen;			/*length of client address data structure*/

	if (ac != 2)	/* test for correct agv */
	{
		fprintf(stderr, "Usage: %s <Server Port>\n", av[0]);
		exit(1);
	}

	echoServPort = atoi(av[1]); /* First arg: local port */

	/* Create socket for incoming connections */
	if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		diewitherror( "socket () failed");

	/* Construct local address structure */
	memset(&echoServAddr, 0, sizeof(echoServAddr)); 	/* Zero out structure */
	echoServAddr.sin_family = AF_INET; 					/* Internet address family*/
	echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); 	/* Any incoming interface */
	echoServAddr.sin_port = htons(echoServPort); 		/* Local port */

	/*Bind to the local address */
	if(bind(servSock, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr)) < 0)
		diewitherror("bind () failed");

	/* Mark the socket so it will listen for incoming connections */
	if (listen(servSock, MAXPENDING) < 0)
		diewitherror("listen() failed");

	while (1)
	{
		/* set the size of the in-out parameter */
		clntLen = sizeof(echoClntAddr);

		/* wait for client to connect */
		if ((clntSock = accept(servSock, (struct sockaddr *)&echoClntAddr, &clntLen)) < 0)
			diewitherror("accept () failed");

		/* clnt sock is connected to a client! */
		printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));
		handleTCPClient(clntSock);
	}
	/* not reached */
}
