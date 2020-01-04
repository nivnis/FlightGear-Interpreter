//
// Created by pikachu on 12/23/19.
//

#include "Client.h"
#include "SymbolTable.h"
#include "Var.h"


Client::Client(string ipn, int portNumber) {
    port = portNumber;
    ip = ipn;

    //create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        exit(2);
    }

    //We need to create a sockaddr obj to hold address of server
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;//IP4
    address.sin_addr.s_addr = inet_addr(ipn.c_str());  //the localhost address
    address.sin_port = htons(port);
    //we need to convert our number (both port & localhost)
    // to a number that the network understands.

    // Requesting a connection with the server on local host with port 8081
    int is_connect = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
    while (is_connect == -1) {
        std::cerr << "Could not connect to host server. Trying again!" << std::endl;
        is_connect = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
    }
    std::cout << "Client is now connected to server" << std::endl;
}

void Client::runClientThread() {
    thread *clientThread = new thread(&Client::runClient, this);
    clientThread->detach();
}


void Client::runClient() {
    while (true) {
        //if here we made a connection
        ////////////////////////////////////////////////////////////////////////////////////
        //HERE I RUN a loop ON THE MAP AND SEND THE VALUES TO THE SIMULATOR!!!
        //string commandString = "set " + symTable.getSim, symtable.getValue;‬;
        queue<string>* clientCommands = SymbolTable::getInstance()->getClientCommands();
        while (!clientCommands->empty()) {
            string command = clientCommands->front().c_str();
            clientCommands->pop();
            //debug
            //string debug = "client: ";
            //cout<< debug + command.c_str()<< std::endl;
            //
            int is_sent = send(client_socket, command.c_str(),command.size() , 0);
            if (is_sent == -1) {
                std::cout << "Error sending message" << std::endl;
            }
            cout<<command.substr(0,command.find('\r')) + " sent to server"<<endl;
        }
    }
    close(client_socket);
}