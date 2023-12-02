
#include <iostream>
#include <string>  

#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h>    

#include <arpa/inet.h>     
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h>

#include "Message.h"
     
#define PORT 8888 
   
// Taken from here i (and modified for clarity and compatability with previous material) :
// https://www.geeksforgeeks.org/socket-programming-in-cc-handling-multiple-clients-on-server-without-multi-threading/

int main(int argc, char *argv[])  
{ 


	// use these strings to indicate the state transitions
        // the robot progresses through.  Do not modify these strings

        std::string robot_waiting = "The robot is waiting";
        std::string robot_moving = "The robot is moving";

        std::string robot_finished_waiting = "The robot finished waiting";
        std::string robot_finished_moving = "The robot finished moving";

        std::string robot_began_waiting = "The robot began waiting";
        std::string robot_begin_moving = "The robot begain moving";

	int counter = -1;

    int opt = true;
    int master_socket, addrlen, new_socket, client_socket[30], 
          max_clients = 30, activity, valread, sd;  
    int max_sd;  
    struct sockaddr_in address;  
         
    char buffer[1025];  //data buffer of 1K + one byte for a NUL terminator  
        
    //std::cout << "Echo server running on port : " << PORT << std::endl;
    //std::cout << "Use telnet localhost " << PORT << " to connect" << std::endl;
    //std::cout << "If connecting from outside the VM, you will need another port fwd" << std::endl;

    // set of socket descriptors 
    fd_set readfds;  
         
    std::string message = "Hello from ECHO Daemon v1.0";  
     
    // initialise all of the client_socket[] array to 0 (not checked) 
    for (size_t i = 0; i < max_clients; i++)  
    {  
        client_socket[i] = 0;  
    }  
         
    //create a master socket 
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)  
    {  
	std::cerr << "socket failed" << std::endl;  
        exit(EXIT_FAILURE);  
    }  
     
    //set master socket to allow multiple connections , 
    //this is just a good habit, it will work without this 
    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, 
          sizeof(opt)) < 0 )  
    {  
	std::cerr << "setsockopt" << std::endl;  
        exit(EXIT_FAILURE);  
    }  
     
    //type of socket created 
    address.sin_family = AF_INET;  
    address.sin_addr.s_addr = INADDR_ANY;  
    address.sin_port = htons( PORT );  
         
    //bind the socket to localhost port 8888 
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)  
    {  
	std::cerr << "bind failed" << std::endl;  
        exit(EXIT_FAILURE);  
    } 

    //else {
	    //counter = 0;
	 //}
    
    //std::cout << "Listener on port : " << PORT << std::endl;  
         
    // specify a maximum of 3 pending connections for the master socket 
    if (listen(master_socket, 3) < 0)  
    {  
	std::cerr << "error listening" << std::endl;  
        exit(EXIT_FAILURE);  
    }  
         
    addrlen = sizeof(address);  
    //std::cout << "Waiting for connections ..." << std::endl;  
         
    while(true)  
    {  

	//counter = 0;

        //clear the socket set 
        FD_ZERO(&readfds);  
     
        //add master socket to set 
        FD_SET(master_socket, &readfds);  
        max_sd = master_socket;  
             
        //add child sockets to set 
        for (size_t i = 0 ; i < max_clients ; i++)  
        {  
            //socket descriptor 
            sd = client_socket[i];  
                 
            //if valid socket descriptor then add to read list 
            if(sd > 0)  
                FD_SET( sd , &readfds);  
                 
            //highest file descriptor number, need it for the select function 
            if(sd > max_sd)  
                max_sd = sd;  
        }  
     
        //wait for an activity on one of the sockets , timeout is NULL , 
        //so wait indefinitely 
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);  
       
        if ((activity < 0) && (errno!=EINTR))  
        {  
		std::cout << "select error" << std::endl;
        }  
             
        // If something happened on the master socket , 
        // then its an incoming connection 
        if (FD_ISSET(master_socket, &readfds))  
        {  
            if ((new_socket = accept(master_socket, 
                    (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)  
            {  
		std::cout << "accept error" << std::endl;  
                exit(EXIT_FAILURE);  
            }  
             
            //inform user of socket number - used in send and receive commands 
	    //std::cout << "New connection , socket fd, ip port " 
                  //<< new_socket  << "," << inet_ntoa(address.sin_addr)  << ntohs(address.sin_port) << std::endl;  
          
	    // convert std::string to char * 
	    char * cstr = message.data();

            //send new connection greeting message 
            if( send(new_socket, cstr, message.size(), 0) != message.size() )  
            {  
                std::cout << " error sending" << std::endl;  
            }  
                 
	    //std::cout << "Welcome message sent successfully" << std::endl;  
                 
            //add new socket to array of sockets 
            for (size_t i = 0; i < max_clients; i++)  
            {  
                //if position is empty 
                if( client_socket[i] == 0 )  
                {

			//this is the important setting it to 0
			//std::cout << "setting counter to 0" << std::endl;
			//counter = 0;

                    client_socket[i] = new_socket;  
		    //std::cout << "Adding to list of sockets as : " << i << std::endl;
                    break;  
                }  
            }  
        }  
             
        // It is some sort of IO operation on some other socket
        for (size_t i = 0; i < max_clients; i++)  
        {  
            sd = client_socket[i];  
                 
            if (FD_ISSET( sd , &readfds))  
            {  
                // Check if it was closing and also read the incoming message 
                if ((valread = read( sd , buffer, 1024)) == 0)  
                {  
                    //Somebody disconnected, get their details and print 
                    getpeername(sd , (struct sockaddr*)&address , \
                        (socklen_t*)&addrlen);  
		    std::cout << "Host disconnected" << std::endl;  
                          //<< inet_ntoa(address.sin_addr) << "," << ntohs(address.sin_port) << std::endl;  
                         
                    // Close the socket and mark as 0 in list for reuse 
                    close( sd );  
                    client_socket[i] = 0;  
                }  
                    	
                // Echo back the message that came in 
                else 
                {  
                    //set the string terminating NULL byte on the end 
                    //of the data read 
                    buffer[valread] = '\0';
		    //std::cout << buffer << std::endl;
		    //
		    //this is the important counter in case you need it
		    //std::cout << counter << std::endl; 
		    //counter += 1;
		    small_world::SM_Event event1;
		    event1.ParseFromString(buffer);
		    if (counter == -1){
			std::cout << robot_began_waiting << std::endl;
		    }
		    if (counter >= 0 && counter < 60){
		    	std::cout << robot_waiting << std::endl;
		    } 
		    if (counter == 60){
			    std::cout << robot_finished_waiting << std::endl;
			    std::cout << robot_begin_moving << std::endl;
		    }
		    if (counter > 60 && counter < 120){
			    std::cout << robot_moving << std::endl;
		    }
		    if (counter == 120) {
			    std::cout << robot_finished_moving << std::endl;
			    std::cout << robot_began_waiting << std::endl;
		    }
		    if (counter > 120) {
			    counter = 0;
		    }
		    counter += 1;
                    send(sd , buffer , valread + 1 , 0 );  
                }  
            }  
        }  
    }  
         
    return EXIT_SUCCESS;  
}  







/*
#include <iostream>

int main(int argc, char * argv[]) {

	// use these strings to indicate the state transitions
	// the robot progresses through.  Do not modify these strings

	std::string robot_waiting = "The robot is waiting";
	std::string robot_moving = "The robot is moving";

	std::string robot_finished_waiting = "The robot finished waiting";
	std::string robot_finished_moving = "The robot finished moving";

	std::string robot_began_waiting = "The robot began waiting";
	std::string robot_begin_moving = "The robot begain moving";

	//std::cout << robot_waiting << std::endl;

	return EXIT_SUCCESS;
}
*/
