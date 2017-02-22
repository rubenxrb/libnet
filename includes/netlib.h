#ifndef NETLIB_H

# define RCVBUFSIZE 32		/* rcv buffer size */
# define MAXQUEUE 5			/* Maximum number of connection requests */

/* External libs */
# include <arpa/inet.h>

/* Structure definitions */
typedef struct	sockaddr_in sockAddrIn;

/* Local headers */
# include "client.h"
# include "server.h"

/* Function headers */
void	exitWithError(char *errorMsg);

#endif
