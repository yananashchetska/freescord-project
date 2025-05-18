/* Yana Nashchetska 12417961 ERASMUS
Je déclare qu'il s'agit de mon propre travail.
Ce travail a été réalisé intégralement par un être humain. */

/*Note :
le code a été écrit à l'aide de modèles dans Moodle,
en complément du code existant.*/

#include <unistd.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list/list.h"
#include "user.h"

#define PORT_FREESCORD 4321

struct list *user_list;
pthread_mutex_t list_mutex = PTHREAD_MUTEX_INITIALIZER;

/** Gérer toutes les communications avec le client renseigné dans
 * user, qui doit être l'adresse d'une struct user */
void *handle_client(void *user);
/** Créer et configurer une socket d'écoute sur le port donné en argument
 * retourne le descripteur de cette socket, ou -1 en cas d'erreur */
int create_listening_sock(uint16_t port);

int main(int argc, char *argv[])
{
	int socket_fd = create_listening_sock(PORT_FREESCORD);
	if (socket_fd < 0)
	{
		perror("Erreur de la création du socket");
		return 1;
	}

	if (listen(socket_fd, 128) < 0)
	{
		perror("Erreur de l'écoute");
		return 1;
	}

	user_list = list_create(); 

	while (1)
	{
		struct user *u = user_accept(socket_fd);
		if (!u)
			continue;

		pthread_t th_id;
		if (pthread_create(&th_id, NULL, handle_client, u) != 0)
		{
			perror("Erreur de pthread_create");
			user_free(u);
			continue;
		}

		pthread_detach(th_id);
	}

	return 0;
}

void *handle_client(void *clt)
{
	struct user *u = (struct user *)clt;

	pthread_mutex_lock(&list_mutex);
	list_add(user_list, u);
	pthread_mutex_unlock(&list_mutex);

	char server_message[] = "Vous êtes connecté sur le serveur.\n";
	write(u->sock, server_message, strlen(server_message));

	char buffer[512];
	ssize_t n;

	while ((n = read(u->sock, buffer, sizeof(buffer))) > 0)
	{
		buffer[n] = '\0';
		printf("On a reçu: %s\n", buffer);

		pthread_mutex_lock(&list_mutex);
		for (struct node *node = user_list->first; node; node = node->next)
		{
			struct user *other = (struct user *)node->elt;
			if (other->sock != u->sock)
			{
				write(other->sock, buffer, n);
			}
		}
		pthread_mutex_unlock(&list_mutex);
	}

	pthread_mutex_lock(&list_mutex);
	list_remove_element(user_list, u);
	pthread_mutex_unlock(&list_mutex);

	user_free(u);
	return NULL;
}

int create_listening_sock(uint16_t port)
{
	int socket_l = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_l < 0)
	{
		perror("socket");
		return -1;
	}

	int opt = 1;
	setsockopt(socket_l, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));

	struct sockaddr_in sa = {
		.sin_family = AF_INET,
		.sin_port = htons(port),
		.sin_addr.s_addr = htonl(INADDR_ANY)};

	if (bind(socket_l, (struct sockaddr *)&sa, sizeof(sa)) < 0)
	{
		perror("bind");
		close(socket_l);
		return -1;
	}

	return socket_l;
}
