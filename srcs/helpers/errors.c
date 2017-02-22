#include <stdio.h>	/* perror() */
#include <stdlib.h>	/* exit() */

void exitWithError(char *errorMsg)
{
	perror(errorMsg);
	exit(1);
}
