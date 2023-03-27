#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>

#define MAX 80
#define SERVER_TCP_PORT 3000	/* well-known port */
#define BUFLEN		256	/* buffer length */
/*send file */
	void send_file(FILE *fp, int sd){
	int n;
	char data [BUFLEN]={0};
	char setbuffer [BUFLEN];

	while ((fgets(data,BUFLEN, fp)) == NULL) {
	if (send(sd, data, sizeof(data),0)== -1){
	perror("file sent: ");
	exit(1);
	}
	
	bzero(setbuffer, BUFLEN);
	char (data);
   }
   
   	bzero(setbuffer, BUFLEN);
   }
  
 
   
int main(int argc, char **argv)
{
	int 	n, i, bytes_to_read;
	int 	sd, port, new_sd;
	struct	hostent		*hp;
	struct	sockaddr_in server, client;
	char	*host, *bp, rbuf[BUFLEN], sbuf[BUFLEN];
	char buffer[BUFLEN] = {0};
FILE *fp;
char *filename = "send.txt";
	
	switch(argc){
	case 2:
		host = argv[1];
		port = SERVER_TCP_PORT;
		break;
	case 3:
		host = argv[1];
		port = atoi(argv[2]);
		break;
	default:
		fprintf(stderr, "Usage: %s host [port]\n", argv[0]);
		exit(1);
	}

	
	/* Create a stream socket	*/	
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		fprintf(stderr, "Can't creat a socket\n");
		exit(1);
	}

	bzero((char *)&server, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	if (hp = gethostbyname(host)) 
	  bcopy(hp->h_addr, (char *)&server.sin_addr, hp->h_length);
	else if ( inet_aton(host, (struct in_addr *) &server.sin_addr) ){
	  fprintf(stderr, "Can't get server's address\n");
	  exit(1);
	}

	/* Connecting to the server */
	if (connect(sd, (struct sockaddr *)&server, sizeof(server)) == -1){
	  fprintf(stderr, "Can't connect \n");
	  exit(1);
	}
	int len = -1;
	printf ("receive: \n");
	
	while (len = read(sd, buffer, BUFLEN)){
		write (1, buffer, len); 
	}
	
	//fp =fopen(filename, "r");
	if (fp == NULL){
	perror("Reading file ");
	exit(1);
	}
	
	send_file (fp, sd);
	printf("data written in file sucessfully \n");
	
	printf("closing the connection \n");
	
	close(sd);
	

	/*printf("Transmit: \n");
	while(n=read(0, sbuf, BUFLEN)){	/* get user message */
	  /*write(sd, sbuf, n);		/* send it out */
	  /*printf("Receive: \n");
	  bp = rbuf;
	  bytes_to_read = n;
	  while ((i = read(sd, bp, bytes_to_read)) > 0){
		bp += i;
		bytes_to_read -=i;
	  }
	  write(1, rbuf, n);
	  printf("Transmit: \n");*/
	//}
	

	return(0);
}
