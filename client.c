#include <netinet/in.h>
#include <stdio.h>
#include <string.h> //strlen
#include <strings.h>
#include <sys/socket.h>
#include <arpa/inet.h> // inet_addr
#include <unistd.h> // close

int main(int argc, char *argv[])
{
    int socket_desc;
    struct sockaddr_in server;
    char message[2000], server_reply[2000];

    socket_desc = socket(AF_INET, SOCK_STREAM, 0); 
    // AF_INET = IPV4
    // SOCK_STREAM = TCP
    // 0 = PROTOCOLO IP

    if (socket_desc == -1) {
        printf("Não foi possivel criar o socket");
        return 1;
    }

    //Informa os dados do servidor para onde vamos nos conectar
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // Converte IP para long
    server.sin_family = AF_INET; //informa que é um IPV4
    server.sin_port = htons(8888);  //Especifica a porta

     //Conecta ao servidor 
    if (connect(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0){
        printf("Erro ao conectar-se\n");
        return 1;
    }

    printf("Conectado.\n");

    do {
        // Limpa a variável com a mensagem
        bzero(message, sizeof(message));
        
        // Envia dados
        printf("Digite uma mensagem: ");

        int ch, n = 0;
        // Le a entrada de dados do usuario via getchar
        while ((ch = getchar()) != '\n' && n < 2000) {
            message[n] = ch;
            ++n;
        }

        if (send(socket_desc, message, strlen(message), 0) < 0){
            printf("Erro ao enviar\n");
            return 1;
        }
        printf("Dados enviados.\n");

         // Recebe dados do servidor
        if (recv(socket_desc, server_reply, 2000, 0) < 0) {
            printf("Falha no recv\n");
            return 1;
        }
        printf("Resposta recebida.\n");
        printf("%s\n", server_reply);

        // Limpa a variável de resposta
        bzero(server_reply, sizeof(server_reply));
    } while (strcmp(message, "exit") != 0);

    close(socket_desc); // fecha o socket

    return 0;
}