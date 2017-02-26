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
	int i = 0;
	int tailleContenu;
	char *mot;
	char *message1;

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
		
		//on est fils
		else if(fok == 0){
			fgets(buff, 256, fsc);
			tailleContenu = strlen(buff);
			//verification de la chaine, doit être de 3 mots, GET / xxx / HTTP/M.m
			i = 1;
			mot = strtok(buff, " ");
			while(mot != NULL && i <= 3){
				//on verifie que le 1er mot est GET, si pas on sort du while
				if(i == 1 && (strncmp(mot, "GET", strlen(mot))) != 0){
					printf("1er mot pas bon\n");
					i = 5;
				}
				//on verifie que le 3eme mot est HTTP/1.0 ou HTTP/1.1, si pas on sort du while
				if(i == 3 && ((strncmp(mot, "HTTP/1.1\r\n", strlen(mot))) != 0 && (strncmp(mot, "HTTP/1.0\r\n", strlen(mot))) != 0)){
					printf("3eme mot pas bon\n");
					i = 5;
				}
				mot = strtok(NULL, " ");
				i++;
			}
		
		
			//on ne fait les traitements suivants que si la premiere ligne est correcte
			if(i == 4){
				message1 = "HTTP/1.1 200 OK\r\nConnection: close\r\nContent-Length: 100\r\n";
				fprintf(fsc, "%s" , message1);
				while(fgets(buff, 256, fsc)){
					tailleContenu += strlen(buff);
					//le if permet d'ignorer les lignes envoyees par le client tant qu'il ne s'agit pas d'une ligne vide
					if(strncmp(buff,"\r\n",2)){
						break;
					}
				}
				fprintf(fsc, "HTTP/1.1 200 OK\r\nConnection: close\r\nContent-Length: %d\r\n", tailleContenu);
			}
			else{
				fprintf(fsc, "HTTP/1.1 400 Bad Request\r\nConnection: close\r\nContent-Length: 17\r\n\r\n400 Bad request\r\n");
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
