#ifndef SERVER_H
#define SERVER_H

int create_server_socket(unsigned short port);
int run_server(int* ssockfd);

#endif // SERVER_H
