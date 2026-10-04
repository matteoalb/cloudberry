#ifndef SOCKET_H
#define SOCKET_H

#include <arpa/inet.h>
#include <vector>
#include <string>

enum class Request { Space, Hierarchy, File, Undefined };
enum class ParseState { Waiting4Header, Waiting4Content };

#pragma pack(push, 1)
struct RawPacketHeader {
    uint32_t length;
    uint8_t request;
};
#pragma pack(pop)

struct PacketHeader {
    uint32_t length;
    Request request = Request::Undefined;
};

struct Client {
	int socket;
	sockaddr_in addr;

    std::vector<uint8_t> buffer;
    ParseState state = ParseState::Waiting4Header;
    PacketHeader header{};
};

std::string GetAddress(const sockaddr_in& addr);
unsigned short GetPort(const sockaddr_in& addr);

class TCPSocket{
    private:
        int mSocket;
    
    public:
        TCPSocket();
        TCPSocket(int sock);
        ~TCPSocket();

        bool Initialized();
        bool Bind(unsigned short port); 
        bool Listen();
        Client Accept();
        bool Send(const void* data, size_t size);
        //bool Receive(std::vector<unsigned char>& buffer);
};


#endif