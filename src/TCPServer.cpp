#include "TCPServer.h"
#include "MySocket.h"

//MySocket serverSocket;

bool forever = true;
int servSock;
struct sockaddr_in serv_addr;
int opt = 1;
int clilen;
int fd;

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
    //masterSocket = serverSocket.MySocket::ServerSocket_new(port);
//    serverSocket->set_NonBlocking(masterSocket);

    
    if((servSock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        //throw socket_error or throw runtime_error
        perror("ServerSocket_new - socket()");   
        exit(EXIT_FAILURE);
        //return(-1);
    }

    if ((fcntl(servSock, F_SETFL, fcntl(servSock, F_GETFL, 0) | O_NONBLOCK)) < 0) {
        perror("ServerSocket_new - fcntl()");
        exit(EXIT_FAILURE);

    }

    if((setsockopt(servSock, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,  sizeof(opt))) < 0 ) {   
        perror("ServerSocket_new - setsockopt()");
        exit(EXIT_FAILURE); 
        //return(-1); 
    }  

    inet_pton(AF_INET, ip_addr, &(serv_addr.sin_addr));
    serv_addr.sin_family       = AF_INET;
    serv_addr.sin_port         = htons(port);

    if ((bind(servSock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))) <0) {
        perror("ServerSocket_new - bind()");
        exit(EXIT_FAILURE);
        //return (-1); 
    }

}

/**********************************************************************************************
 * listenSvr - Performs a loop to look for connections and create TCPConn objects to handle
 *             them. Also loops through the list of connections and handles data received and
 *             sending of data. 
 *
 *    Throws: socket_error for recoverable errors, runtime_error for unrecoverable types
 **********************************************************************************************/

void TCPServer::listenSvr() {
    if ((listen(accept_fd, 10)) < 0) {
            perror("ServerSocket_new:");
            exit(EXIT_FAILURE);
            //return (-1);
        }

    while(forever) {
    //     serverSocket.ServerSocket_accept(masterSocket);
        clilen = sizeof(serv_addr);
        fd = accept(accept_fd, (struct sockaddr *) &cli_addr, &clilen);
        if (fd < 0) {
            perror("ServerSocket_accept");
            exit(EXIT_FAILURE);
        }
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



