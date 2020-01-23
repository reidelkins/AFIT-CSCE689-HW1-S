#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "Client.h"
#include <netinet/in.h>

// The amount to read in before we send a packet
const unsigned int stdin_bufsize = 50;
const unsigned int socket_bufsize = 100;

class TCPClient : public Client
{
public:
   TCPClient();
   ~TCPClient();

   virtual void connectTo(const char *ip_addr, unsigned short port);
   virtual void handleConnection();

   virtual void closeConn();

private:
   int cliSock;
   struct sockaddr_in servAddr;
};


#endif
