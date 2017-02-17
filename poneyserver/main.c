#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "socket.h"
#include <signal.h>
#include <stdlib.h>
#include <wait.h>

//indique au gestionnaire de signaux qu'il doit ignorer le signal SIGPIPE pour que le serveur ne s'arrête pas même si le descripteur de socket est fermé
void initialiser_signaux(void){
	
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR){
		perror("signal");
	}
	
}

//deux fonctions pour faire disparaitre le processus zombie
void traitement_signal(int sig){
	printf("Signal %d reçu\n", sig);
	pid_t p;
// test si il reste d'autre fils, pour nettoyertous les zombis, sil y en a plusieurs killé en même temps
	int status;
	while((p = waitpid(-1, &status, WNOHANG))> 0)
	{
		printf("Fils %d nettoyé\n", p);
		if (WIFSIGNALED(status))
		{
			printf("Fils terminé par le signal %d\n", WTERMSIG(status));
		}
	}
}

void daryl_signal(void){
	struct sigaction sa;
	sa.sa_handler = traitement_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL)==-1){
		perror("sigaction(SIGCHLD)");
	}
}

int main(int argc, char **argv)
{
	int socket_serveur;
	int socket_client;
	char buff[256];

	FILE *fsc; //pour utiliser avec fgets, fprintf...

	
	initialiser_signaux();
	socket_serveur = creer_serveur(8080);
	if(socket_serveur == -1){
		perror("socket_serveur");
		return -1;
	}
	while(1){
		socket_client = accept(socket_serveur, NULL, NULL);
		fsc = fdopen(socket_client, "w+");
		daryl_signal();
		if (socket_client == -1){
			perror("accept");
			return -1;
		}
		pid_t fok = fork();
		if(fok == -1){
			perror("erreur de fork");
			return -1;
		}
		else if(fok == 0){
			//on est fils

			while(fgets(buff, 256, fsc)){
				fprintf(stdout, "%s", buff);
			}
			exit(0);
		}
		else{
			//on est dans le papa 
			close(socket_client);
		}


	}
	
	if (argc > 1 && strcmp(argv[1], "-advice") == 0){
		printf("Don't Panic !\n");
		return 42;
	}
	printf("Need an advice?\n");
	return 0;
}

//char *fgets(char *s, int size, FILE *stream)
//char *fprintf(FILE *stream, const char *format,...) 
