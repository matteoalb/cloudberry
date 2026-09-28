#include "client.h"
#include "socket.h"

#include <iostream>
#include <unistd.h>

TCPSocket c_serverSocket;

int c_initialize(){

    if (!c_serverSocket.Initialized())
        return -1;

    // Connecting the socket and waiting for input
    if (!c_serverSocket.Bind(inet_addr("127.0.0.1"), 6666))
        return -1;

    //if(!serverSocket.Listen())
    //    return -1;

    std::cout << "Client connected on port 6666..." << std::endl;

    return 0;
}

void c_update(){
    u_int32_t len = 0;
    uint8_t requestType = 0;

    std::cin >> requestType;

    if(std::cin.fail())
        std::cin.clear();

    RawPacketHeader header{htonl(len), requestType};
    bool sent = c_serverSocket.Send(&header, sizeof(header));

    if(!sent)
        std::cout << "Error while sending..." << std::endl;
}

void c_shutdown(){
    
}