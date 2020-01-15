// #include "Socket.h"

// typedef int ServerSocket;
// typedef int socket;
// int accept_fd;

// MySocket::MySocket() {};
// MySocket::~MySocket() {};

// ServerSocket MySocket::ServerSocket_new(int port) {
//     accept_fd = accept4(AF_INET, SOCK_STREAM, 0, SOCK_NONBLOCK);
//     if(accept_fd == 0) {
//         //throw socket_error or throw runtime_error
//         perror("ServerSocket_new");   
//         return(-1);
//     }

//     if( setsockopt(accept_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,  sizeof(opt)) < 0 ) {   
//         perror("ServerSocket_new");   
//         return(-1); 
//     }  

//     serv_addr.sin_family       = AF_INET;
//     serv_addr.sin_addr.s_addr  = htonl(INADDR_ANY);
//     serv_addr.sin_port         = htons(port);

//     if (bind(accept_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
//         perror("ServerSocket_new:");
//         return (-1);
//     }

//     if (listen(accept_fd, 10) < 0) {
//         perror("ServerSocket_new:");
//         return (-1);
//     }
//     return accept_fd;

// }

// socket MySocket::ServerSocket_accept(ServerSocket sd) {
//     int fd;

//     struct   sockaddr_in  serv_addr;
//     int clilen;

//     clilen = sizeof(cli_addr);
//     fd = accept(sd, (struct sockaddr *) &cli_addr, &clilen);
//     if (fd < 0) {
//         perror("ServerSocket_accept");
//         return (-1);
//     }
//     return fd;
// }

// // void MySocket::set_NonBlocking(socket sd) {
// //     #ifdef _WIN32
// //         return (ioctlsocket(fd, FIONBIO, &mode) == 0) ? true : false;
// //     #else
// //         int flags = fcntl(fd, F_GETFL, 0);
// //         if (flags == -1) return false;
// //         flags = blocking ? (flags & ~O_NONBLOCK) : (flags | O_NONBLOCK);
// //         return (fcntl(fd, F_SETFL, flags) == 0) ? true : false;
// //     #endif

// //     int status = fcntl(socketfd, F_SETFL, fcntl(socketfd, F_GETFL, 0) | O_NONBLOCK);

// //     if (status == -1){
// //         perror("calling fcntl");
// //     }
// // }


