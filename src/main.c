#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

void print_usage() {
    printf("Usage: echo [options]\n");
    printf("Options:\n");
    printf("  -h, --help\tShow this help message\n");
    printf("  -p, --port\tPort the program will use to serve. (Default: 7. Needs superuser permissions in most systems)\n");
}

int main(int argc, char *argv[]) 
{ 
    unsigned short port = 7; // Default ECHO port (RFC 862)

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_usage();
            exit(0);
        } 
        else if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--port") == 0) {
            if (i + 1 < argc) {
                port = (unsigned short) atoi(argv[i + 1]);
                i++;
            } else {
                printf("Error: -p/--port option requires a port number\n");
                print_usage();
                exit(1);
            }
        } 
        else {
            printf("Unknown option: %s\n", argv[i]);
            print_usage();
            exit(1);
        }
    }

    int server_socket = create_server_socket(port);
    if(server_socket == -1) {
        print_usage();
        exit(1);
    }
    return run_server(&server_socket);
}
