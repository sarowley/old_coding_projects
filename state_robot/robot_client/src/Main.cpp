
// From here : https://www.geeksforgeeks.org/socket-programming-cc/


#include <iostream>

#include <string.h>   //strlen 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h>   //close 
#include <arpa/inet.h>    //close 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros 
   
#include <fstream>
#include "Message.h"

#define TRUE   1 
#define FALSE  0 
#define PORT 8888 
    

int main(int argc, char const* argv[])
{
    int status, valread, client_fd;
    struct sockaddr_in serv_addr;
    std::string hello("tick");


    small_world::SM_Event cm;
    cm.set_event_type("TICK");
    cm.set_event_time("0");

    std::string message;

    char buffer[1024] = { 0 };
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
	    std::cout << "\n Socket creation error \n" << std::endl;
        return -1;
    }
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
  
    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
        <= 0) {
        std::cout <<  
            "\nInvalid address/ Address not supported \n" << std::endl;
        return -1;
    }
  
    if ((status
         = connect(client_fd, (struct sockaddr*)&serv_addr,
                   sizeof(serv_addr)))
        < 0) {
	    std::cout << "\nConnection Failed \n" << std::endl;
        return -1;
    }
    while (true){
    usleep(500000);
    //send(client_fd, hello.c_str(), hello.length(), 0);
    cm.SerializeToString(&message);
    send(client_fd, message.c_str(), message.length(), 0);
    std::cout << "\n";
    valread = read(client_fd, buffer, 1024);
    //std::cout << "%s\n" << buffer << std::endl;
    }
  
    // closing the connected socket
    close(client_fd);
    return 0;
}
