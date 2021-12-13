#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>


int main (int argc, char *argv []){
	int sockClient, port = 8080, st, countsend, countrev;
	struct sockaddr_in server;
	char message[2000], receive[2000], temp;
	
	sockClient = socket(AF_INET, SOCK_STREAM, 0);

	if(sockClient < 0){printf("REFUSE ! NO SOCKET ACCEPT\n");}
	else { printf("SUCCESFULLY CONNECTED!\n");}

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("192.168.56.7");
	server.sin_port = htons(port);

	st = connect (sockClient, (struct sockaddr *)&server, sizeof(server));

	if(st == -1){
	   printf("REFUSE CONNECT!");
	   perror("ERROR");
	}
	else {printf("SUCCESS!");}
	while(strncmp(receive, "STOP", 8) != 0){
	   printf(" FROM CLIENT: ");
	   scanf("%c", &temp);
	   scanf("%[^\n]", message);

	   countsend = send(sockClient, message, strlen(message), 0);
	   memset(receive, 0, 1000);

	   if(countsend < 0){
	      printf("NOT ENOUGH\n");
	      return 1;
	   }
	
	   countrev = recv(sockClient, receive, 2000, 0);

	   if(countrev < 0){ printf("ERROR OCCUR! NOT RECEIVED\n");}
	   printf("FROM SERVER: ");
	   puts(receive);
	}
	close(sockClient);

}
