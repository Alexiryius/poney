#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "socket.h"

int main(int argc, char **argv)
{
	int socket_serveur;
	int socket_client;
	socket_serveur = creer_serveur(8080);
	while(1){
		socket_client = accept(socket_serveur, NULL, NULL);
		if (socket_client == -1){
			perror("accept");
			return -1;
		}
		const char *message_bienvenue = "Bonjour, bienvenue sur mon serveur Bonjour, 		bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur \n";
		write(socket_client, message_bienvenue, strlen(message_bienvenue));
	}
	/* Arnold Robbins in the LJ of February '95, describing RCS */
	if (argc > 1 && strcmp(argv[1], "-advice") == 0){
		printf("Don't Panic !\n");
		return 42;
	}
	printf("Need an advice?\n");
	return 0;
}
