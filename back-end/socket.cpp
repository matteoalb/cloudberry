#include "socket.h"

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>


TCPSocket::TCPSocket(){
    mSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    fcntl(mSocket, F_SETFL, O_NONBLOCK);
};

TCPSocket::~TCPSocket(){
    if(!Initialized())
        return;

    close(mSocket);
};

bool TCPSocket::Initialized(){ return mSocket!=-1; }

bool TCPSocket::Bind(unsigned short port){
    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
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
    }else{
        // Printing client IP Address
        char buff[INET6_ADDRSTRLEN] = {0};
        std::cout << "Client connected: " 
                    << inet_ntop(clientAddr.sin_family, (void*)&(clientAddr.sin_addr), buff, INET6_ADDRSTRLEN)
                    << std::endl;
        client.addr = clientAddr;
    }

    return client;
}


bool TCPSocket::Send(const unsigned char* data, unsigned short len){
    unsigned short networkLen = htons(len);
	return send(mSocket, reinterpret_cast<const char*>(& networkLen), sizeof(networkLen), 0) == sizeof(networkLen)
		&& send(mSocket, reinterpret_cast<const char*>(data), len, 0) == len;
}

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