#include "TCPServer.h"
#include "MySocket.h"

MySocket serverSocket;

bool forever = true;

TCPServer::TCPServer() {

}


TCPServer::~TCPServer() {
    
}

/**********************************************************************************************
 * bindSvr - Creates a network socket and sets it nonblocking so we can loop through looking for
 *           data. Then binds it to the ip address and port
 *
 *    Throws: socket_error for recoverable errors, runtime_error for unrecoverable types
 **********************************************************************************************/

void TCPServer::bindSvr(const char *ip_addr, short unsigned int port) {
   //int masterSocket = serverSocket->ServerSocket_new(port);
//    serverSocket->set_NonBlocking(masterSocket);
}

/**********************************************************************************************
 * listenSvr - Performs a loop to look for connections and create TCPConn objects to handle
 *             them. Also loops through the list of connections and handles data received and
 *             sending of data. 
 *
 *    Throws: socket_error for recoverable errors, runtime_error for unrecoverable types
 **********************************************************************************************/

void TCPServer::listenSvr() {
    while(forever) {
     //   serverSocket->ServerSocket_accept(serverSocket->ServerSocket sd);
    }


}

/**********************************************************************************************
 * shutdown - Cleanly closes the socket FD.
 *
 *    Throws: socket_error for recoverable errors, runtime_error for unrecoverable types
 **********************************************************************************************/

void TCPServer::shutdown() {
   // close();
    //need to provide the socket that is closed?
}



