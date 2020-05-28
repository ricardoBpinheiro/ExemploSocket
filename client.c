#include <stdio.h>
#include <sys/socket.h>

int main(int argc, char *argv[]){
    
    int socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    // AF_INET = IPV4
    // SOCK_STREAM = TCP
    // 0 = PROTOCOLO IP

    if (socket_desc == -1) {
        printf("Não foi possivel criar o socket");
        return 1;
    }

    return 0;
}