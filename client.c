#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/if.h>

int main(int argc , char *argv[])
{
    //socket的建立
    int sockfd = 0;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1){
        printf("Fail to create a socket.");
    }

    //socket的連線
    struct sockaddr_in remote_info;
    bzero(&remote_info,sizeof(remote_info));
    remote_info.sin_family = AF_INET;

    remote_info.sin_addr.s_addr = inet_addr("172.27.114.31");

    remote_info.sin_port = htons(8700);

    //localinfo(client info)
    struct sockaddr_in client_info;

    client_info.sin_family = AF_INET;
    client_info.sin_addr.s_addr = inet_addr("172.27.120.132");

    //bind sockfd to local network interface
    bind(sockfd, (struct sockaddr*)&client_info, sizeof(client_info));

//another method to bind client side network interface using setsockopt() with SO_BINDTODEVICE option 
/***********************************************************************************************************
    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));
    snprintf(ifr.ifr_name, sizeof(ifr.ifr_name),"rename3");

    if(setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE, (void*)&ifr, sizeof(ifr)) < 0){
        printf("bind sockfd to network interface failded,return value is\n");
    }else{
        printf("bind sockfd to network interface successed\n");
    }
 ************************************************************************************************************/

    int err = connect(sockfd,(struct sockaddr *)&remote_info,sizeof(remote_info));
    if(err==-1){
        printf("Connection error");
    }


    //Send a message to server
    char message[] = {"Hi there"};
    char receiveMessage[100] = {};
    send(sockfd,message,sizeof(message),0);
    recv(sockfd,receiveMessage,sizeof(receiveMessage),0);

    printf("\n%s",receiveMessage);
    printf("close Socket\n");
    close(sockfd);
    return 0;
}
