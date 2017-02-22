#ifndef NETLIB_CLIENT_H

/* Structure definitions */
typedef struct		s_client
{
	int				sockDesc;
	sockAddrIn		sockAddr;
	unsigned short	sockPort;
}					t_client;

/* Function headers */
t_client		*newTCPClnt(const char *servIp);	/* zero out unused data */
void			deleteClnt(t_client *clnt);			/* free & close sockDesc */

#endif
