#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "socket.h"
#include <signal.h>

//indique au gestionnaire de signaux qu'il doit ignorer le signal SIGPIPE pour que le serveur ne s'arrête pas même si le descripteur de socket est fermé
void initialiser_signaux(void){
	
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR){
		perror("signal");
	}
}

int main(int argc, char **argv)
{
	int socket_serveur;
	int socket_client;
	//int nb;
	//char buff[256];
	const char *message_bienvenue = "Bonjour, bienvenue sur mon serveur Bonjour, 		bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur Bonjour, bienvenue sur mon serveur \n";

	initialiser_signaux();
	socket_serveur = creer_serveur(8080);
	if(socket_serveur == -1){
		perror("socket_serveur");
		return -1;
	} 
	while(1){
		socket_client = accept(socket_serveur, NULL, NULL);
		if (socket_client == -1){
			perror("accept");
			return -1;
		}


//crée une boucle d'envoi infini pour si on arrete la boucle constater que ca eteint le serveur si on utilise pas la fonction signal. Si on utilise signal ca ne doit pas l'arreter
		while(1){
			write(socket_client, message_bienvenue, strlen(message_bienvenue));
		}
		
		
		/*while((nb = read(socket_client, buff, 256)) > 0){
			write(socket_client, buff, nb);
		}*/
		
		
	}
	close(socket_client);
	/* Arnold Robbins in the LJ of February '95, describing RCS */
	if (argc > 1 && strcmp(argv[1], "-advice") == 0){
		printf("Don't Panic !\n");
		return 42;
	}
	printf("Need an advice?\n");
	return 0;
}
