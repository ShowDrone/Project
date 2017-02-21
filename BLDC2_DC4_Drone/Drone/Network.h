
#include <stdio.h>
#include <string.h>     
#include <sys/socket.h> 
#include <arpa/inet.h>  
#include <unistd.h>  

#define TAM_MAX_MENSAGEM_BOAS_VINDAS   300  
#define TAM_MAX_MENSAGEM_STATUS_LED    100  
#define w        2000  
#define NUM_MAX_CONEXAO_CLIENTS        1  
#define GPIO_LED                       2    
#define PORTA_SOCKET_SERVER            8888

int  getControlData();
double controlSpeed();

