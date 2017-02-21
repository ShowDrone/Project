
#include "Network.h"


int socket_desc , client_sock , c , read_size; 
struct sockaddr_in server , client;                      //server: socket information´s structure (server side)
double throttleMin; 
double throttleMax;
double currentSpeed;

int  getControlData() {
		char client_message[TAM_MAX_MENSAGEM_CLIENT];           //buffer of messages sent by client
		char MensagemBoasvindas[TAM_MAX_MENSAGEM_BOAS_VINDAS];   //contains welcome messagem (sent to client when it connects to server)
		char MensagemStatusLed[TAM_MAX_MENSAGEM_STATUS_LED];     //contains led status´s message 

		socket_desc = socket(AF_INET , SOCK_STREAM , 0);
		if (socket_desc == -1) {
			printf("Error during socket creation");
		}
		puts("Socket successfully created!");
     
		server.sin_family = AF_INET;
		server.sin_addr.s_addr = INADDR_ANY;
		server.sin_port = htons( PORTA_SOCKET_SERVER );
    
		if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0) {
			perror("Error in bind");
			return 1;
		}
		puts("Bind is done!");
     
		listen(socket_desc , NUM_MAX_CONEXAO_CLIENTS);
     
		puts("Waiting for connection...");
		c = sizeof(struct sockaddr_in);
	
		client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
	
		if (client_sock < 0) {
			perror("Error: connection is not established");
			return 1;
		}
		puts("Connection established! Socket is read for read and write data now.");
    
		sprintf(MensagemBoasvindas,"Welcome to Intel Edison Socket\n\rYour IP: %s\n\n\r", inet_ntoa(client.sin_addr));
		write(client_sock , MensagemBoasvindas , strlen(MensagemBoasvindas));
	
		char msg[10];
		while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 ) {
			if (client_message[4]=='1') 	{
				//Pad 1 Left
				memset(msg, ' ', sizeof(msg));
				strncpy(msg, client_message+4, 7);
				printf("pad 1: %s \n\r", msg);
				//pulseTime = 1700;  차후 주석 풀어라
			}
	
			if (client_message[4]=='2') {
				//Pad 2 Right
				memset(msg, ' ', sizeof(msg));
				strncpy(msg, client_message+4, 7);
				printf("pad 2: %s \n\r", msg);
			}
	
		memset(client_message,0,TAM_MAX_MENSAGEM_CLIENT);
		}
    
		if(read_size == 0) {
			puts("Client is desconnnected. This program is terminating right now.");
			fflush(stdout);
			close(client_sock);   
		}
		else if(read_size == -1)  {
			perror("recv failed. This program is terminating right now");
		}	
}
