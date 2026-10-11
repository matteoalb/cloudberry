#ifndef RASPBERRY_H
#define RASPBERRY_H

#include <string>
#include <vector>
#include "socket.h"

int initialize();
void update();
void shutdown();
void ManageClients();
void ParseClientRequest(Client& client);
void ProcessRequest(Client& client, std::vector<uint8_t>& content);

#endif