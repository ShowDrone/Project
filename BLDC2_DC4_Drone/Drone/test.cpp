/*----------------------------------------------------------------------------
* Program: TCP Socket communication in C (compiled and running on Linux)
* Hardware: Intel Edison + Arduino Expansion Board + Base Shield
*
* Created by: Pedro Bertoleti												 
------------------------------------------------------------------------------*/
//includes
#include<stdio.h>
#include<string.h>     
#include<sys/socket.h> 
#include<arpa/inet.h>  
#include<unistd.h>     
//#include "mraa.hpp"    
  
//defines
#define TAM_MAX_MENSAGEM_BOAS_VINDAS   300   //max. length of welcome message
#define TAM_MAX_MENSAGEM_STATUS_LED    100   //max lendth of led status´ message'
#define w        2000  //max length of client message (message sent by client)
#define NUM_MAX_CONEXAO_CLIENTS        1     //max number of connections 
#define GPIO_LED                       2      //GPIO that led is located
#define PORTA_SOCKET_SERVER            8888   //Socket port. Note: this value must be something between 2000 and 65535.   If the chosen port is already in use, change this define for another port number and try again
                                              

int main(int argc , char *argv[])
{
    int socket_desc , client_sock , c , read_size;      //socket_desc: server socket descriptor
	                                                    //client_sock: client connection´s descriptor		
														//read_size: contains socket struct size 
    struct sockaddr_in server , client;                      //server: socket information´s structure (server side)
	                                                         //client: socket information´s structure (client side) 
    char client_message[TAM_MAX_MENSAGEM_CLIENT];           //buffer of messages sent by client
    char MensagemBoasvindas[TAM_MAX_MENSAGEM_BOAS_VINDAS];   //contains welcome messagem (sent to client when it connects to server)
	char MensagemStatusLed[TAM_MAX_MENSAGEM_STATUS_LED];     //contains led status´s message 

    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Error during socket creation");
    }
    puts("Socket successfully created!");
     
	server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( PORTA_SOCKET_SERVER );
    
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("Error in bind");
        return 1;
    }
    puts("Bind is done!");
     
    //Put socket server in listening state. This program will stuck here until a connection attempt is not received
    listen(socket_desc , NUM_MAX_CONEXAO_CLIENTS);
     
    //A socket connecting attempt was received. Now it´s time for trying establish connection.
    puts("Waiting for connection...");
    c = sizeof(struct sockaddr_in);
	
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
	
	//check if connection was established
	if (client_sock < 0)
	{
		perror("Error: connection is not established");
		return 1;
	}
	puts("Connection established! Socket is read for read and write data now.");
    
	//Welcome message
	sprintf(MensagemBoasvindas,"Welcome to Intel Edison Socket\n\rYour IP: %s\n\n\r", inet_ntoa(client.sin_addr));
	write(client_sock , MensagemBoasvindas , strlen(MensagemBoasvindas));
	
    char msg[10];
	//Program will run on this loop until the connection is on
	while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
	{
		//There´s client a message. Now it´s time to check if it´s a valid command
		if (client_message[4]=='1')
		{
			//Pad 1
            memset(msg, ' ', sizeof(msg));
            strncpy(msg, client_message+4, 7);
			printf("pad 1: %s \n\r", msg);

            pulseTime = 1700;

            
            
			/*
            while(1) {
                d1_pin->write(1);
                d2_pin->write(1);
                usleep(pulseTime);
                d1_pin->write(0);
                d2_pin->write(0);
                usleep(10000-(pulseTime));
            }
			*/
        }
	
		if (client_message[4]=='2')
		{
			//Pad 2
            memset(msg, ' ', sizeof(msg));
            strncpy(msg, client_message+4, 7);
			printf("pad 2: %s \n\r", msg);
		}
	
		memset(client_message,0,TAM_MAX_MENSAGEM_CLIENT);
	}
    
	//If program reaches here, the socket connection is over. The program will notify user and terminate.
	if(read_size == 0)
	{
		puts("Client is desconnnected. This program is terminating right now.");
		fflush(stdout);
		close(client_sock);   
	}
	else if(read_size == -1)  //if a read error occurs, the program terminate too.
	{
		perror("recv failed. This program is terminating right now");
	}
    
	return 0;
}
