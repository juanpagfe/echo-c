#include <stdio.h>
#if defined(_WIN32) || defined(_WIN64)
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

// Function for Windows
int get_max_tcp_clients() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed.\n");
        return -1;
    }

    DWORD maxSockets;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result == 0) {
        maxSockets = wsaData.iMaxSockets;
        WSACleanup();
        return maxSockets;
    } else {
        fprintf(stderr, "Unable to retrieve max sockets.\n");
        return -1;
    }
}

#else
#include <sys/resource.h>

// Function for POSIX systems (Linux, macOS, etc.)
int get_max_tcp_clients() {
    struct rlimit rl;
    if (getrlimit(RLIMIT_NOFILE, &rl) != 0) {
        printf("getrlimit failed");
        return -1;
    }

    return (int)rl.rlim_cur;
}
#endif
