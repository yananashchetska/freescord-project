/* Yana Nashchetska 12417961 ERASMUS
Je déclare qu'il s'agit de mon propre travail.
Ce travail a été réalisé intégralement par un être humain. */

/*Note :
le code a été écrit à l'aide de modèles dans Moodle,
en complément du code existant.*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include "user.h"

struct user *user_accept(int sock_listen)
{
	struct sockaddr_in *addr = malloc(sizeof(struct sockaddr_in));
	if (!addr)
		return NULL;

	struct user *u = malloc(sizeof(struct user));
	if (!u)
	{
		free(addr);
		return NULL;
	}

	u->addr_len = sizeof(struct sockaddr_in);
	int s = accept(sock_listen, (struct sockaddr *)addr, &u->addr_len);
	if (s < 0)
	{
		perror("accept");
		free(addr);
		free(u);
		return NULL;
	}

	u->address = (struct sockaddr *)addr;
	u->sock = s;

	return u;
}

void user_free(struct user *u)
{
	if (!u)
		return;
	close(u->sock);
	free(u->address);
	free(u);
}