#include "raspberry.h"
#include "socket.h"

#include <iostream>
#include <unistd.h>
#include <cstring>

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

    // Accept new connections
    Client client = serverSocket.Accept();
    if(client.socket != -1){
        clients.push_back(client);
    }

    // Manage Connected/Disconnected clients
    ManageClients();

    for(Client& c: clients){
        ParseClientRequest(c);
    }
}

void shutdown(){
    for(int i=0; i<clients.size(); i++){
        std::cout << "Disconnecting client" << std::endl;
        close(clients[i].socket);
    }
    clients = {};
}

void ManageClients(){
    auto itClient = clients.begin();
    while ( itClient != clients.end() )
    {
        const std::string clientAddress = GetAddress(itClient->addr);
        char buffer[200] = { 0 };
        bool disconnect = false;

        // RECEPTION
        int ret = recv(itClient->socket, buffer, 199, 0);
        if (ret == 0)
        {
            // Client disconnected
            disconnect = true;
        }
        if (ret == -1)
        {
            if (errno != static_cast<int>(EWOULDBLOCK))
            {
                // Issue with client connection
                disconnect = true;
            }
            // Nothing to read from client
        }
        else if(ret>0){
            // Adding received message to processing queue
            itClient->buffer.insert(itClient->buffer.end(), buffer, buffer+ret);
        }

        // DISCONNECTING CLIENT
        if (disconnect)
        {
            std::cout << "Disconnecting client: " << clientAddress << std::endl;
            itClient = clients.erase(itClient);
        }
        else
            ++itClient;
    }
}

void ParseClientRequest(Client& client){

    if(client.state == ParseState::Waiting4Header){
        if (client.buffer.size() < sizeof(RawPacketHeader))
            return;

        RawPacketHeader rawHeader;
        std::memcpy(&rawHeader, client.buffer.data(), sizeof(RawPacketHeader));

        client.header.length = ntohl(rawHeader.length);
        client.header.request = static_cast<Request>(rawHeader.request);

        client.buffer.erase(client.buffer.begin(), client.buffer.begin() + sizeof(RawPacketHeader));
        client.state = ParseState::Waiting4Content;
    }
    
    if(client.state == ParseState::Waiting4Content){
        if (client.buffer.size() < client.header.length)
            return;
        
        std::vector<uint8_t> content(
            client.buffer.begin(),
            client.buffer.begin() + client.header.length
        );

        client.buffer.erase(client.buffer.begin(), client.buffer.begin() + client.header.length);

        ProcessRequest(client, content);

        client.state = ParseState::Waiting4Header;
    }
}

void ProcessRequest(Client& client, std::vector<uint8_t>& content){
    // Processing the request here
    switch (client.header.request)
    {
    case Request::Space:
        std::cout << "Requesting available space";
        break;
    
    case Request::Hierarchy:
        std::cout << "Requesting current hierarchy";
        break;

    case Request::File:
        std::cout << "Requesting specific file";
        break;
    
    default:
        std::cout << "Undefined request, skipping...";
        break;
    }

    client.header={};
}