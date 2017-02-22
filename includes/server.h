#ifndef NETLIB_SERVER_H

/* Structure definitions */
typedef struct		s_server
{
	int				sockDesc;
	sockAddrIn		sockAddr;
	unsigned short	sockPort;
}					t_server;

/* Function headers */
t_server		*newTCPServ(const short port);	/* returns valid tcpserv */
void			deleteServ(t_server *serv);		/* free & close sockServ */

#endif
