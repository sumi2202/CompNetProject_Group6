/* A simple echo server using TCP */
#include <stdio.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <arpa/inet.h> 
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <pthread.h>

#define SERVER_TCP_PORT 3000	/* well-known port */
#define BUFLEN		256	/* buffer length */

	void write_file(int sd){
	int n;
	FILE *fp;
	char *filename= "send.txt";
	char setbuffer[BUFLEN];
	
	fp = fopen(filename, "w");
	while(1){
	n = recv(sd, setbuffer, BUFLEN,0);
	if (n<=0){
	break;
	return;
	}
	fprintf(fp, "%s", setbuffer);
	bzero(setbuffer, BUFLEN);
	}
	return;

int echod(int);
void reaper(int);

int main(int argc, char **argv)
{
	int 	sd, new_sd, client_len, port;
	struct	sockaddr_in server, client;
	socklen_t addr_size;
	
	
	switch(argc){
	case 1:
		port = SERVER_TCP_PORT;
		break;
	case 2:
		port = atoi(argv[1]);
		break;
	default:
		fprintf(stderr, "Usage: %s [port]\n", argv[0]);
		exit(1);
	}

	/* Create a stream socket	*/	
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		fprintf(stderr, "Can't creat a socket\n");
		exit(1);
	}

	/* Bind an address to the socket	*/
	bzero((char *)&server, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sd, (struct sockaddr *)&server, sizeof(server)) == -1){
		fprintf(stderr, "Can't bind name to socket\n");
		exit(1);
	}

	/* queue up to 5 connect requests  */
	listen(sd, 5);

	(void) signal(SIGCHLD, reaper);

	while(1) {
	  client_len = sizeof(client);
	  new_sd = accept(sd, (struct sockaddr *)&client, &client_len);
	  if(new_sd < 0){
	    fprintf(stderr, "Can't accept client \n");
	    exit(1);
	  }
	  switch (fork()){
	  case 0:		/* child */
		(void) close(sd);
		exit(echod(new_sd));
	  default:		/* parent */
		(void) close(new_sd);
		break;
	  case -1:
		fprintf(stderr, "fork: error\n");
	  }
	  addr_size = sizeof(client);
	  new_sd = accept(sd, (struct sockaddr*)&client, &addr_size);
	  write_file(new_sd);
	  printf("data written in file successfully\n");
	}
	
	
}

/*	echod program	*/
int echod(int sd)
{
	int n, bytes_to_read;
	char buffer[BUFLEN] = "hello \n";
	 	n = strlen(buffer);

		write(sd, buffer, n);
	close(sd);

	return(0);
}

/*	reaper		*/
void	reaper(int sig)
{
	int	status;
	while(wait3(&status, WNOHANG, (struct rusage *)0) >= 0);
}
