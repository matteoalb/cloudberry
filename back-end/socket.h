#ifndef SOCKET_H
#define SOCKET_H

#include <arpa/inet.h>
#include <vector>

struct Client {
	int socket;
	sockaddr_in addr;
};


class TCPSocket{
    private:
        int mSocket;
    
    public:
        TCPSocket();
        ~TCPSocket();

        bool Initialized();
        bool Bind(unsigned short port); 
        bool Listen();
        Client Accept();
        bool Send(const unsigned char* data, unsigned short len);
        bool Receive(std::vector<unsigned char>& buffer);
};


#endif