#include <sys/socket.h>
#include <fcntl.h>

class MySocket
{
public:
   MySocket();
   ~MySocket();

   typedef int serverSocket;
   typedef int socket;

    serverSocket ServerSocket_new(int port);


    socket ServerSocket_accept(serverSocket sd);


    socket Socket_new(char * host, int port);

    int Socket_getc(socket sd);



    int Socket_putc(int c, socket sd);


    int Socket_close(socket sd);

    // void set_NonBlocking(socket sd);

   

private:
   


};