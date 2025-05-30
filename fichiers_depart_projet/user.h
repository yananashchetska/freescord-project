/* Yana Nashchetska 12417961 ERASMUS
Je déclare qu'il s'agit de mon propre travail.
Ce travail a été réalisé intégralement par un être humain. */

/*Note :
le code a été écrit à l'aide de modèles dans Moodle,
en complément du code existant.*/

#ifndef USER_H
#define USER_H
#include <sys/socket.h>
#include <netinet/in.h>

struct user
{
	struct sockaddr *address;
	socklen_t addr_len;
	int sock;
	/* autres champs éventuels */
};

struct user *user_accept(int sock_listen);
void user_free(struct user *user);

#endif /* ifndef USER_H */
