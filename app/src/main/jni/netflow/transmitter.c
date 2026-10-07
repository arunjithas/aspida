#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<errno.h>
#include<netinet/udp.h>
#include<netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "transmitter.h"
#include "config.h"
#include "global.h"
#include "common/utils.h"

int sockfd = -1;
struct sockaddr_in server_addr;

int sendData(char *pydata, int pydatalen,const char *dstIP,int dstport)
{

    // Create UDP socket
    if (sockfd == -1){
        // Create a socket
        if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
            log_d("socket creation failed");
            sockfd = -1;
            return -1;
        }
        // Fill server information
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(dstport);
        server_addr.sin_addr.s_addr = inet_addr(dstIP);

    }

    if (sockfd < 0) {
        log_d("socket creation failed");
        return -1;
    }



    // Send data
    // char *message = "Hello, UDP Server!";
    if (sendto(sockfd, (const char *)pydata, pydatalen, 0, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        log_d("sendto failed");
        sockfd = -1;
        close(sockfd);
    }

    log_d("Data sent to server.\n");

    // Close the socket
    // close(sockfd);


    return 0;
}


