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
    sockfd = socket(AF_INET , SOCK_STREAM , 0);

    if (sockfd == -1){
        printf("Fail to create a socket.");
    }

    //socket的連線
    struct sockaddr_in remoteinfo;
    bzero(&remoteinfo,sizeof(remoteinfo));
    remoteinfo.sin_family = PF_INET;

    //remoteinfo(server info)
    remoteinfo.sin_addr.s_addr = inet_addr("127.0.0.1");
    remoteinfo.sin_port = htons(8700);

    //localinfo(client info)
    struct sockaddr_in localaddr = {0};
    localaddr.sin_family = AF_INET;
//    localaddr.sin_addr.s_addr = inet_addr("192.168.2.102");
    localaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    //bind sockfd to local network interface
    bind(sockfd, (struct sockaddr*)&localaddr, sizeof(localaddr));

//another method to bind client side network interface using setsockopt() with SO_BINDTODEVICE option 
/***********************************************************************************************************
    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));
    snprintf(ifr.ifr_name, sizeof(ifr.ifr_name),"enp0s8");
    printf("ifr_name is %s\n",ifr.ifr_name);
    char *interface_name;
    interface_name = "enp0s8\0";

    int r =0;

//    if(setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE, (void*)&ifr, sizeof(ifr))<0){
    if(setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE, interface_name, 7)<0){
        printf("bind sockfd to network interface failded,return value is %d\n", r = setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE, interface_name, 7));
	int err = errno;
	fprintf(stderr, "%s\n", explain_errno_setsockopt(err,sockfd,SOL_SOCKET,SO_BINDTODEVICE,interface_name,7));
	exit(EXIT_FAILURE);
    }else{
        printf("bind sockfd to network interface successed\n");
    }
************************************************************************************************************/

    int err = connect(sockfd,(struct sockaddr *)&info,sizeof(info));
    if(err==-1){
        printf("Connection error");
    }


    //Send a message to server
    char message[] = {"Hi there"};
    char receiveMessage[100] = {};
    send(sockfd,message,sizeof(message),0);
    recv(sockfd,receiveMessage,sizeof(receiveMessage),0);

    printf("%s",receiveMessage);
    for(;;){}
    printf("close Socket\n");
    close(sockfd);
    return 0;
}
