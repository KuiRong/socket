#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc , char *argv[])

{
    //socket的建立
    char inputBuffer[256] = {};
    char message[] = {"Hi,this is server.\n"};
    int sockfd = 0,clientsockfd = 0;
    sockfd = socket(AF_INET , SOCK_STREAM , 0);

    if (sockfd == -1){
        printf("Fail to create a socket.");
    }

    //socket的連線
    struct sockaddr_in serverinfo, clientinfo;
    int addrlen = sizeof(clientinfo);

    // struct in_addr client_address = clientinfo.sin_addr;
    char addr_str[INET_ADDRSTRLEN];

    bzero(&serverinfo,sizeof(serverinfo));

    serverinfo.sin_family = PF_INET;
    serverinfo.sin_addr.s_addr = INADDR_ANY;
    serverinfo.sin_port = htons(8700);
    bind(sockfd,(struct sockaddr *)&serverinfo,sizeof(serverinfo));

    listen(sockfd,5);

    // struct sockaddr_in peer;
    // socklen_t peer_len;

    while(1){
        clientsockfd = accept(sockfd,(struct sockaddr*) &clientinfo, &addrlen);
        send(clientsockfd,message,sizeof(message),0);
        recv(clientsockfd,inputBuffer,sizeof(inputBuffer),0);
        printf("Get:%s\n",inputBuffer);
//        inet_ntop(AF_INET, &client_address, addr_str, INET_ADDRSTRLEN);
        inet_ntop(AF_INET, &(clientinfo.sin_addr), addr_str, INET_ADDRSTRLEN);

        printf("IP address is %s \n",addr_str);

        // if(getpeername(sockfd, &peer, &peer_len)){
        //     printf("client peer is %d\n", peer.sin_addr.s_addr);
        //     printf("client address is\n");
        //     inet_ntop(AF_INET, &client_address, addr_str, INET_ADDRSTRLEN);
        //     printf("IP address is %d \n",inet_ntoa(clientinfo.sin_addr));
        // }
    }
    return 0;
}
