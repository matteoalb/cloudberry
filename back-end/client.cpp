#include "client.h"
#include "socket.h"

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>

TCPSocket* c_serverSocket = nullptr;

const char* piname = "127.0.0.1";

bool connect_to_server(){
    addrinfo hints{};
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    addrinfo* res = nullptr;
    int err = getaddrinfo(piname, "6666", &hints, &res);
    if (err != 0) {
        std::cerr << "Couldn't get Raspberry's IP: " << gai_strerror(err) << std::endl;
        return false;
    }

    int sock = -1;

    for (addrinfo* p = res; p != nullptr; p = p->ai_next) {
        sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sock < 0) continue;

        if (connect(sock, p->ai_addr, p->ai_addrlen) == 0)
            break;

        close(sock);
        sock = -1;
    }
    freeaddrinfo(res);

    if(sock < 0){
        std::cerr << "Couldn't connect to Pi..." << std::endl;
        return false;
    }
    c_serverSocket = new TCPSocket(sock);

    return true;
}

int c_initialize(){

    if(!connect_to_server())
        return -1;

    std::cout << "Client connected to Raspberry Pi" << std::endl;

    return 0;
}

void c_update(){
    int requestType = 0;

    if (!(std::cin >> requestType)) {
        if (std::cin.eof())
            return;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    std::cout << "Sending request: " << requestType << std::endl;

    RawPacketHeader header{htonl(0), (uint8_t)requestType};
    bool sent = c_serverSocket->Send(&header, sizeof(header));

    if(!sent)
        std::cout << "Error while sending..." << std::endl;
}

void c_shutdown(){
    delete c_serverSocket;
    c_serverSocket = nullptr;
}