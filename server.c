#include <netinet/in.h>
#include <stdio.h>   
#include <string.h>	//strlen
#include <sys/socket.h>
#include <arpa/inet.h> // inet_addr
#include <unistd.h>  // close

int main(int argc, char *argv[]){
    
    int socket_desc;
    struct sockaddr_in server;
    
    // Abre um socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Não foi possivel criar o socket");
        return 1;
    }

    //onde eu quero ouvir
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY; //Escute em qualquer IP da maquina
    server.sin_port = htons(8888);


    //vincula o socket a porta e ao endereço informados
    if(bind(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0){
        printf("Erro ao fazer o bind\n");
        return 1;
    }

    printf("Bind efetuado.\n");
    return 0;
}