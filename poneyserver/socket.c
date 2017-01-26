#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include "socket.h"

int creer_serveur(int port){
	int socket_serveur;
	//int socket_client;
	struct sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = INADDR_ANY;

	socket_serveur = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_serveur == -1){
		perror("socket_serveur");
		return -1;
	}
	if (bind(socket_serveur, (struct sockaddr *) &saddr, sizeof(saddr)) ==-1){
		perror("bind socket_serveur");
		return -1;
	}
	if(listen(socket_serveur, 10) ==-1){
		perror("listen socket_serveur");
		return -1;
	}

	/*socket_client = accept(socket_serveur, NULL, NULL);
	if (socket_client === -1){
		perror("accept");
	}
	const char *message_bienvenue = "Bonjour, bienvenue sur mon serveur Bonjour, 		bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur \n";
	write(socket_client, message_bienvenue, strlen(message_bienvenue));*/

	return socket_serveur;
}


