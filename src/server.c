#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <arpa/inet.h> 
#include <unistd.h>
#include <poll.h>
#include "utils.h"
#define BUF_SIZE 1024 

int create_server_socket(unsigned short port) {
    int sockfd;
    struct sockaddr_in servaddr; 

    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("Socket creation failed\n"); 
        return -1; 
    }

    memset(&servaddr, 0, sizeof(servaddr)); 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(port); 

    if ((bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) != 0) { 
        printf("Socket bind failed on port %d.\n", port); 
        return -1; 
    } 

    if ((listen(sockfd, 5)) != 0) { 
        printf("Server listen failed on port %d.\n", port); 
        exit(1); 
    } else {
        printf("Listening on port = %d\n", port);
    }
    return sockfd;
}

int run_server(int* ssockfd) 
{ 
    int max_clients = get_max_tcp_clients();
    struct pollfd pfds[get_max_tcp_clients()];
    pfds[0].fd = *ssockfd;
    pfds[0].events = POLLIN | POLLPRI;
    int clients = 1;


    while(1) {
        int pollResult = poll(pfds, clients + 1, -1);
        if (pollResult > 0)
        {
            if (pfds[0].revents & POLLIN)
            {
                struct sockaddr_in cliaddr;
                socklen_t addrlen = sizeof(cliaddr);
                int client_socket = accept(*ssockfd, (struct sockaddr *)&cliaddr, &addrlen);
                printf("Client accepted %s:%d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
                for (int i = 1; i < max_clients; i++)
                {
                    if (pfds[i].fd == 0)
                    {

                        pfds[i].fd = client_socket;
                        pfds[i].events = POLLIN | POLLPRI;
                        clients++;
                        break;
                    }
                }
            }
            for (int i = 1; i < clients; i++)
            {
                if (pfds[i].fd > 0 && pfds[i].revents & POLLIN)
                {
                    char buf[BUF_SIZE];
                    int bufSize = read(pfds[i].fd, buf, BUF_SIZE);
                    if (bufSize == -1 || bufSize == 0)
                    {
                        pfds[i].fd = 0;
                        pfds[i].events = 0;
                        pfds[i].revents = 0;
                        clients--;
                    }
                    else
                    {
                        write(pfds[i].fd, buf, bufSize);
                    }
                }
            }
        }
    }
    return 0;
}
