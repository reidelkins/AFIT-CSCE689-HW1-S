#include "TCPClient.h"


struct sockaddr_in servAddr;
struct hostent *addr;
int status;
int opt = 1;


/**********************************************************************************************
 * TCPClient (constructor) - Creates a Stdin file descriptor to simplify handling of user input. 
 *
 **********************************************************************************************/

TCPClient::TCPClient() {
    
}

/**********************************************************************************************
 * TCPClient (destructor) - No cleanup right now
 *
 **********************************************************************************************/

TCPClient::~TCPClient() {

}

/**********************************************************************************************
 * connectTo - Opens a File Descriptor socket to the IP address and port given in the
 *             parameters using a TCP connection.
 *
 *    Throws: socket_error exception if failed. socket_error is a child class of runtime_error
 **********************************************************************************************/

void TCPClient::connectTo(const char *ip_addr, unsigned short port) {
    //30 lines
    int thisSock;
    struct sockaddr_in tmpAddr;


    if((thisSock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        //throw socket_error or throw runtime_error
        perror("TCPClient - socket");   
        exit(EXIT_FAILURE);
        //return(-1);
    }

    // if ((fcntl(cliSock, F_SETFL, fcntl(cliSock, F_GETFL, 0) | O_NONBLOCK)) < 0) {
    //     perror("TCPClient - fcntl");
    //     exit(EXIT_FAILURE);
    //     //return(-1);
    // }

    // if((setsockopt(cliSock, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,  sizeof(opt))) < 0 ) {   
    //     perror("TCPClient - setsockopt");
    //     exit(EXIT_FAILURE); 
    //     //return(-1); 
    // }  

    if( inet_pton(AF_INET, ip_addr, &tmpAddr.sin_addr) <=0) { 
        perror("\nInvalid address/ Address not supported \n"); 
        exit(EXIT_FAILURE); 
    }
    servAddr.sin_family       = AF_INET;
    servAddr.sin_port         = htons(port);

   
    if(connect(thisSock, (struct sockaddr *)&tmpAddr, sizeof(tmpAddr)) < 0) {
        perror("TCPClient - connect");
        exit(EXIT_FAILURE);
    }
    
    printf("Hello, you have successfully connected to the server\n");
    printf("Possible commands are:\n");
    printf("'hello'\n");
    printf("'1'\n");
    printf("'2'\n");
    printf("'3'\n");
    printf("'4'\n");
    printf("'5'\n");
    printf("'passwd'\n");
    printf("'exit'\n");
    printf("'menu'\n");
         
    TCPClient::cliSock = thisSock;
    TCPClient::servAddr = tmpAddr;
    

}

/**********************************************************************************************
 * handleConnection - Performs a loop that checks if the connection is still open, then 
 *                    looks for user input and sends it if available. Finally, looks for data
 *                    on the socket and sends it.
 * 
 *    Throws: socket_error for recoverable errors, runtime_error for unrecoverable types
 **********************************************************************************************/

void TCPClient::handleConnection() {
   //20 lines
    int thisSock = TCPClient::cliSock;
    struct sockaddr_in tmpAddr = TCPClient::servAddr;
    bool forever = true;

    char inBuff[1024] = {0};
    char outBuff[1024] = {0};
    int servVal, myVal;
    std::string delimiter = "\n";
    size_t position = 0;
    std::string command;


    std::string input(inBuff,0);

    while(forever) {
        servVal = read( thisSock , inBuff, 1024);
        inBuff[servVal] = '\0';
        printf("%s\n\n", inBuff);

        myVal = read(STDIN_FILENO, outBuff,1024);
        outBuff[myVal] = '\0';

        if( send(thisSock, outBuff, myVal,0) != strlen(outBuff) ) {
            perror("send");
        }

        input = std::string(outBuff, myVal);
        position = 0;

        while((position = input.find(delimiter)) != std::string::npos) {
            command = input.substr(0,position);
            input.erase(0,position + delimiter.length());

            if(command == "exit")
            {
                forever = false;
            }

        }
        


   }
}

/**********************************************************************************************
 * closeConnection - Your comments here
 *
 *    Throws: socket_error for recoverable errors, runtime_error for unrecoverable types
 **********************************************************************************************/

void TCPClient::closeConn() {
    close(TCPClient::cliSock);
}


