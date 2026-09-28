#include "socket.h"

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>


TCPSocket::TCPSocket(){
    mSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Set socket to non-blocking
    fcntl(mSocket, F_SETFL, O_NONBLOCK);
};

TCPSocket::~TCPSocket(){
    if(!Initialized())
        return;

    close(mSocket);
};

bool TCPSocket::Initialized(){ return mSocket!=-1; }

bool TCPSocket::Bind(unsigned short port){
    return TCPSocket::Bind(INADDR_ANY, port);
}

bool TCPSocket::Bind(in_addr_t addr, unsigned short port){
    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = addr;
    server.sin_port = htons(port);
    
    if(bind(mSocket, (const sockaddr*)&server, sizeof(server)) == -1){
        std::cerr << "Couldn't bind to desired port: " << strerror(errno) << std::endl;
        return false;
    }
    return true;
};

bool TCPSocket::Listen(){
    if (listen(mSocket, SOMAXCONN) == -1) {
        std::cerr << "listen() failed: " << strerror(errno) << std::endl;
        return false;
    }
    return true;
}

Client TCPSocket::Accept(){
    sockaddr_in clientAddr{};
    socklen_t len = sizeof(clientAddr);

    Client client = {};
    client.socket = accept(mSocket, (sockaddr*)&clientAddr, &len);
    if (client.socket == -1) {
        if (errno == EWOULDBLOCK || errno == EAGAIN) {
            return client;
        }

        std::cerr << "accept() failed: " << strerror(errno) << std::endl;
        close(client.socket);
        return client;
    }

    // Setting client socket to non-blocking
    if(fcntl(client.socket, F_SETFL, O_NONBLOCK)){
        std::cerr << "Couldn't set client socket to non-blocking: " << strerror(errno) << std::endl;
        close(client.socket);
        return client;
    }

    // Printing client IP Address
    std::cout << "Client connected: " 
                << GetAddress(clientAddr)
                << std::endl;
    client.addr = clientAddr;
    

    return client;
}


bool TCPSocket::Send(const void* data, size_t size){
    const char* ptr = static_cast<const char*>(data);
    size_t totalSent = 0;

    while (totalSent < size) {
        int sent = send(mSocket, ptr + totalSent, static_cast<int>(size - totalSent), 0);
        if (sent <= 0) {
            return false; // error or connection closed
        }
        totalSent += sent;
    }
    return true;
}

/*
bool TCPSocket::Receive(std::vector<unsigned char>& buffer){
    unsigned short expectedSize;
	int pending = recv(mSocket, reinterpret_cast<char*>(&expectedSize), sizeof(expectedSize), 0);
	if ( pending <= 0 || pending != sizeof(unsigned short) )
	{
		// Top of buffer doesn't contain the size of a valid packet
		return false;
	}
	
	expectedSize = ntohs(expectedSize);
	buffer.resize(expectedSize);
	int receivedSize = 0;
	do {
		int ret = recv(mSocket, reinterpret_cast<char*>(&buffer[receivedSize]), (expectedSize - receivedSize) * sizeof(unsigned char), 0);
		if ( ret <= 0 )
		{
			// Not enought data to load, looping until all the data arrives
			buffer.clear();
			return false;
		}
		else
		{
			receivedSize += ret;
		}
	} while ( receivedSize < expectedSize );
	return true;
}
*/

std::string GetAddress(const sockaddr_in& addr)
{
	char buff[INET6_ADDRSTRLEN] = { 0 };
	return inet_ntop(addr.sin_family, (void*)&(addr.sin_addr), buff, INET6_ADDRSTRLEN);
}

unsigned short GetPort(const sockaddr_in& addr){
        return ntohs(addr.sin_port);
}