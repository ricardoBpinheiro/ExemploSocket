#include <netinet/in.h>
#include <stdio.h>   
#include <string.h>	//strlen
#include <sys/socket.h>
#include <arpa/inet.h> // inet_addr
#include <unistd.h>  // close

int main(int argc, char *argv[]){
    
    int socket_desc;
    struct sockaddr_in server;
    char *message, server_reply[2000]; 

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    // AF_INET = IPV4
    // SOCK_STREAM = TCP
    // 0 = PROTOCOLO IP

    if (socket_desc == -1) {
        printf("Não foi possivel criar o socket");
        return 1;
    }

    //Informa os dados do servidor para onde vamos nos conectar
    server.sin_addr.s_addr = inet_addr("172.217.28.132");  // Converte IP para long
    server.sin_family = AF_INET; //informa que é um IPV4
    server.sin_port = htons(80);  //Especifica a porta


    //Conecta ao servidor 
    if (connect(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0){
        printf("Erro ao conectar-se\n");
        return 1;
    }

    printf("Conectado.\n");

    //Envia dados
    message = "GET / HTTP/1.1\r\n\r\n";

    if(send(socket_desc, message, strlen(message), 0) < 0){
        printf("Erro ao enviar\n");
        return 1;
    }
    printf("Dados Enviados.\n");

    // Recebe dados do servidor
    if (recv(socket_desc, server_reply, 2000, 0) < 0){
        printf("Falha no recv\n");
        return 1;
    }
    printf("Resposta Recebida.\n");
    printf("%s\n", server_reply);

    close(socket_desc); //fecha o socket

    return 0;
}