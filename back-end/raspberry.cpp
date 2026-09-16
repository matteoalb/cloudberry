#include "raspberry.h"
#include "socket.h"

#include <iostream>
#include <unistd.h>

TCPSocket serverSocket;
std::vector<Client> clients;

int initialize(){

    if (!serverSocket.Initialized())
        return -1;

    // Connecting the socket and waiting for input
    if (!serverSocket.Bind(6666))
        return -1;

    if(!serverSocket.Listen())
        return -1;

    std::cout << "CloudBerry listening on port 6666..." << std::endl;

    return 0;
}

void update(){
    Client client = serverSocket.Accept();
    if(client.socket != -1){
        clients.push_back(client);
    }
}

void shutdown(){
    for(int i=0; i<clients.size(); i++){
        std::cout << "Disconnecting client" << std::endl;
        close(clients[i].socket);
    }
    clients = {};
}