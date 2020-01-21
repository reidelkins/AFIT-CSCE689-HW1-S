#include "TCPServer.h"

#include <fcntl.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string>

#include <unistd.h>   //close  

#include <string.h>
#include <cerrno>

struct sockaddr_in serv_addr, cli_addr;
bool forever = true;
int servSock, activity, clientSocks[30], sd, cliLen, newSock;
int opt = 1;
fd_set incomingFDs;


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
        perror("bindSvr - socket()");   
        exit(EXIT_FAILURE);
        //return(-1);
    }
    if ((fcntl(servSock, F_SETFL, fcntl(servSock, F_GETFL, 0) | O_NONBLOCK)) < 0) {
        perror("bindSvr - fcntl()");
        exit(EXIT_FAILURE);

    }
    if((setsockopt(servSock, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,  sizeof(opt))) < 0 ) {   
        perror("bindSvr - setsockopt()");
        exit(EXIT_FAILURE); 
        //return(-1); 
    }  

    inet_pton(AF_INET, ip_addr, &(serv_addr.sin_addr));
    serv_addr.sin_family       = AF_INET;
    serv_addr.sin_port         = htons(port);

    int servAddrLen = sizeof(serv_addr);
    if ((bind(servSock, (struct sockaddr *)&serv_addr, servAddrLen)) <0) {
        perror("bindSvr - bind()");
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
//int TCPServer::listenSvr() {
    char buffer[1025];
    int valRead;
    //std::cout << ("-----------------------------------------------------------");
    
    if ((listen(servSock, 10)) < 0) {
            perror("TCPServer - listen");
            exit(EXIT_FAILURE);
            //return (-1);
        }
    
    while(forever) {
    //     serverSocket.ServerSocket_accept(masterSocket);

        FD_ZERO(&incomingFDs);
        FD_SET(servSock, &incomingFDs); 
		int maxSD = servSock;

        for ( int i = 0 ; i < maxSD ; i++) { 
			//socket descriptor 
			sd = clientSocks[i]; 
				
			//if valid socket descriptor then add to read list 
			if(sd > 0) {
				FD_SET( sd , &incomingFDs); 
            }
			//highest file descriptor number, need it for the select function 
			if(sd > maxSD) 
				maxSD = sd; 
		} 
        activity = select( maxSD + 1 , &incomingFDs , NULL , NULL , NULL);
        if (( activity < 0) && (errno!=EINTR) ) {
            perror("TCPServer - select");

        }
        
        if (FD_ISSET(servSock, &incomingFDs)) { 
			if ( (newSock = accept(servSock, (struct sockaddr *)&cli_addr, (socklen_t*)&cliLen) ) <0) { 
				perror("TCPServer - accept"); 
				exit(EXIT_FAILURE); 
			}

            for (int i = 0; i < maxSD; i++) { 
				//if position is empty 
				if( clientSocks[i] == 0 ) { 
					clientSocks[i] = newSock; 
						
					break; 
				} 
			}
        }

        for (int i = 0; i < maxSD; i++) { 
			sd = clientSocks[i]; 
				
			if (FD_ISSET( sd , &incomingFDs)) 
			{ 
				//Check if it was for closing , and also read the 
				//incoming message 
				if ((valRead = read( sd , buffer, 1024)) == 0) { 	
					//Close the socket and mark as 0 in list for reuse 
					close( sd ); 
					clientSocks[i] = 0; 
				} else {
                
                    buffer[valRead] = '\0';
                    std::string incoming(buffer, strlen(buffer));
                    std::string msg = "";

                    std::string delimiter = "\n";
                    size_t position = 0;
                    std::string command;

                    
                    while((position = incoming.find(delimiter)) != std::string::npos) { //strip out commands if sent multiple at once
                        command = incoming.substr(0,position);
                        incoming.erase(0,position + delimiter.length());

                        if(command == "hello") {
                            msg = "howdy";
                        } else if (command == "1") {
                            msg = "Tractorcito is the nickname for this seasons NFL rushing leader";

                        } else if (command == "2" ) {
                            msg = "North Korea and Cuba are the only countries where Coke is not sold";

                        } else if (command == "3") {
                            msg = "The canary islands are named after dogs, not birds";

                        } else if (command == "6") {
                            msg = "Robin Williams questioned if god was crazy because of a platypus";

                        } else if (command == "5") {
                            msg = "Microsoft's headquarters is home to the quietest room on earth";

                        } else if (command == "passwd" ) {
                            msg = "password received";

                        } else if (command == "exit" ) {
                            //NEED TO CLOSE SOCKET NOW
                            msg = "ending connection";

                        } else if (command == "menu" ) {
                            msg = "Possible Commands: hello, 1, 2, 3, 4, 5, passwd, exit, menu";

                        } else {
                            msg = "That was not a valid command";
                            //DO I FULLY CLOSE SOCKET CONNECTION???

                        }

                        int outlen = msg.length() + 1;
                        char buffer_out[outlen + 1]; //create buffer

                        strcpy(buffer_out,msg.c_str());
                        buffer_out[outlen+1] = '\0'; //recast and add null
                    
                        if( send(sd,buffer_out,strlen(buffer_out),0) != strlen(buffer_out) ) //reply to client
                        {
                            perror("send");
                        }
                    } 
				} 
			} 
		}

    }

}

/**********************************************************************************************
 * shutdown - Cleanly closes the socket FD.
 *
 *    Throws: socket_error for recoverable errors, runtime_error for unrecoverable types
 **********************************************************************************************/

void TCPServer::shutdown() {
    //sd.close();
    close(servSock);
    //need to provide the socket that is closed?
}
