/* <arpa/inet.h> */
typedef struct		sockaddr
{
	unsigned short	sa_family;		/* address family (AF_INET, AP_INET, etc) */
	unsigned char	sa_data[14];	/* family-specific address information */
}					sockaddr;

typedef struct		in_addr
{
	unsigned int	s_addr;	/* (4 bytes) */
}					in_add;

typedef struct		sockaddr_in
{
	unsigned short	sin_family;	/* Internet protocol (AF_INET) */
	unsigned short	sin_port;	/* address port (2 bytes) */
	in_add			sin_addr;	/* internet address (4 bytes) */
	unsigned char	sin_zer[8]; /* Not used */
}					sockaddr_in;

/* <sys/socket.h> */
int socket(int protocolfamily, int type, int protocol);
int connect(int socket, sockaddr *foreignAddress, unsigned int addressLen);
int send(int socket, const void *msg, unsigned int msgLen, int flags);
int recv(int socket, void *rcvBuffer, unsigned int buffLen, int flags);

/* <unistd.h> */
int close(int socket);

/*
 * ip = 4 ints that represent bytes "1.255.180.165.255" -> unsig chars (0 - 255)
 * internet addresses are 32-bit (4 unsigned chars)
 * port number = 16-bit (2 unsigned chars) -> range from 1 - 65,535 (0 reserved)
 *
 * communcation = server - client relationship
 * client initialites communication, server program waits.
 * the program sets those roles, depending on how is using the sockets API
 * client needs to know the server's address and port. not viceversa.
 * there are different assigned port numbers (IANA)
 *
 * socket = abstraction through which a program may send and recieve data.
 * socket allows a program to "connect" to the network and communicate with
 * other applications "connected" in the same network.
 * stream sockets = TCP (IP underneath) byte-stream service
 * datagram sockets = UDP (IP underneath) sends messages up to ~65,500 bytes
 *
 * IP -> TCP/UDP protocol -> TCP/UDP port number -> Sockets bound to ports ->
 * TCP/UDP sockets -> descriptor references -> programs
 *
 * a TCP/UDP port number identifies a socket on a host
 *
 * <sys/types.h> (optional compatibility)
 * <sys/socket.h>
 * int socket(int protocolfamily, int type, int protocol)
 * PF_INET = ip protocol family
 * SOCK_STREAM = stream socket type / SOCK_DGRAM = datagram socket type
 * IPPROTO_TCP = TCP protocol / IPPROTO_UDP = UDP protocol
 * protocol 0 specifies default protocol for specified protocol family and type
 * socket() returns: (socket descriptor) for succes, (-1) for failure, like fd.
 * int close(int socket) -> close socket that is no longer needed
 *
 *	 (sa_family)			(sa_data)
 *	 |------------------------------------------------|
 *	 |family	 |		Blob (14 bytes)			  	  | sockaddr struct
 *	 |------------------------------------------------|
 *	 |2 bytes	 |2 bytes	|4 bytes	|8 bytes 	  |
 *	 |------------------------------------------------|
 *	 |family	 |port		|ip (&)		|(unused)	  | sockaddr_in struct
 *	 |------------------------------------------------|
 *	 (sin_family)(sin_port)	(sin_addr)	(sin_zero)
 *
 *	----- TCP Client -----
 *	1. Create TCP socket using socket();
 *	2. Establich a connection to the server using connect();
 *	3. Communicate using send() and recv();
 *	4. Close the connection with close();
 *	----------------------
 *
 * int connect(int socket, sockaddr *foreignAddress, unsigned int addressLen);
 * socket = socket descriptor, addressLen = sizeof(sockaddr_in)
 *
 * int send(int socket, const void *msg, unsigned int msgLen, int flags);
 * int recv(int socket, void *rcvBuffer, unsigned int buffLen, int flags);
 * socket = socket descriptor, buffLen = max # of bytes it can recieve
 * both functions return the number of bytes sent/recieved, (-1) if fail
 *
 */
