#include <netinet/in.h>
#include <stdio.h>
#include <string.h> //strlen
#include <sys/socket.h>
#include <arpa/inet.h> // inet_addr
#include <unistd.h>  // close

int main(int argc, char *argv[])
{
    int socket_desc, c, new_socket;
    struct sockaddr_in server, client;
    char *message, client_reply[2000];

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

    //escutar
    listen(socket_desc, 3);

    //aceitar conexoes entrantes
    printf("Aguardando conexões...\n");
    c = sizeof(struct sockaddr_in);
    while ((new_socket = accept(socket_desc, (struct sockaddr *) &client, (socklen_t*) &c))){
        char *client_ip = inet_ntoa(client.sin_addr);
        int client_port = ntohs(client.sin_port);

        printf("Conexão aceita do client %s:%d\n", client_ip, client_port);

        do {
            //Limpa a variável char[]
            bzero(client_reply, sizeof(client_reply)); 
            //Recebe dados do cliente 
            if (recv(new_socket, client_reply, 2000, 0) < 0){
                printf("Falha no recv\n");
                return 1;
            }
            printf("Resposta recebida.");
            printf("%s\n", client_reply);

            //Responde ao cliente
            write(new_socket, message, strlen(message));
        } while(strcmp(client_reply, "exit") != 0);
    }

    if (new_socket < 0) {
        printf("Erro ao aceitar conexão\n");
        return 1;
    }

    return 0;
}
