//
// Created by pikachu on 12/23/19.
//

#include "Server.h"
#include "SymbolTable.h"
#include "Var.h"
//
// Created by pikachu on 12/22/19.
//
#include "Server.h"

Server::Server(int portNumber):port(portNumber)
{
    makeSimArray();
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        exit(1);
    }

    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(port);
    //we need to convert our number
    // to a number that the network understands.

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr<<"Could not bind the socket to an IP"<<std::endl;
        exit(1);
    }

    //making socket listen to the port
    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
        std::cerr<<"Error during listening command"<<std::endl;
        exit(1);
    } else{
        std::cout<<"Server is now listening ..."<<std::endl;
    }

    // accepting a Client
    client_socket = accept(socketfd, (struct sockaddr *)&address,
                               (socklen_t*)&address);
    if (client_socket == -1) {
        std::cerr<<"Error accepting Client"<<std::endl;
    }
    close(socketfd); //closing the listening socket
}

void Server::runServerThread() {
    //open a thread on the heap and start updating the map
    thread* serverThread = new thread(&Server::runServer,this);
    serverThread->detach();
}


void Server::runServer() {
//reading from Client
    char buffer[1024];
    bzero(buffer, 1024);
    string data, curr_data;
    vector<float> valVector;

    while (true) {
        int i = 0;
        int valread = read(client_socket, buffer, 1024);
        data.append(buffer, valread);
        //while we didn't meet the '\n'
        while (!data.find('\n')) {
            valread = read(client_socket, buffer, 1024);
            data.append(buffer, valread);
        }
        //curr_data is our float now
        curr_data = data.substr(0, data.find('\n'));
        data.erase(0, data.find('\n') + 1);
        valVector = getValVector(curr_data);
        //HERE I UPDATE THE VAR MAP BY SIM
        SymbolTable* symbolTable = SymbolTable::getInstance();
        for (float value : valVector) {
            symbolTable->setVarBySim(this->simArr[i%36],value);
            i++;
        }
    }
}

vector<float> Server::getValVector(string s) {
    char delimiter = ',';
    size_t pos = 0;
    std::string token;
    vector<float> vector;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        //std::cout << token << std::endl;
        vector.push_back(stof(token));
        s.erase(0, pos + 1);
    }
    //std::cout << s << std::endl;
    vector.push_back(stof(s));
    return vector;
}

void Server::makeSimArray(){
    this->simArr[airspeed] = "/instrumentation/airspeed-indicator/indicated-speed-kt";
    this->simArr[warp] = "/sim/time/warp";
    this->simArr[magnetos] = "/controls/switches/magnetos";
    this->simArr[heading] = "/instrumentation/heading-indicator/offset-deg";
    this->simArr[alt] = "/instrumentation/altimeter/indicated-altitude-ft";
    this->simArr[pressure] = "/instrumentation/altimeter/pressure-alt-ft";
    this->simArr[pitch] = "/instrumentation/attitude-indicator/indicated-pitch-deg";
    this->simArr[roll] = "/instrumentation/attitude-indicator/indicated-roll-deg";
    this->simArr[internal_pitch] = "/instrumentation/attitude-indicator/internal-pitch-deg";
    this->simArr[internal_roll] = "/instrumentation/attitude-indicator/internal-roll-deg";
    this->simArr[encoder_alt] = "/instrumentation/encoder/indicated-altitude-ft";
    this->simArr[encoder_pressure] = "/instrumentation/encoder/pressure-alt-ft";
    this->simArr[gps_alt] = "/instrumentation/gps/indicated-altitude-ft";
    this->simArr[gps_ground_speed] = "/instrumentation/gps/indicated-ground-speed-kt";
    this->simArr[gps_vertical_speed] = "/instrumentation/gps/indicated-vertical-speed";
    this->simArr[indicated_heading] = "/instrumentation/heading-indicator/indicated-heading-deg";
    this->simArr[compass] = "/instrumentation/magnetic-compass/indicated-heading-deg";
    this->simArr[slip_skid] = "/instrumentation/slip-skid-ball/indicated-slip-skid";
    this->simArr[turn_rate] = "/instrumentation/turn-indicator/indicated-turn-rate";
    this->simArr[indicated_speed] = "/instrumentation/vertical-speed-indicator/indicated-speed-fpm";
    this->simArr[aileron] = "/controls/flight/aileron";
    this->simArr[elevator] = "/controls/flight/elevator";
    this->simArr[rudder] = "/controls/flight/rudder";
    this->simArr[flaps] = "/controls/flight/flaps";
    this->simArr[engine_throttle] = "/controls/engines/engine/throttle";
    this->simArr[curr_engine_throttle] = "/controls/engines/current-engine/throttle";
    this->simArr[master_avionics] = "/controls/switches/master-avionics";
    this->simArr[starter] = "/controls/switches/starter";
    this->simArr[auto_start] = "/engines/active-engine/auto-start";
    this->simArr[speedbrake] = "/controls/flight/speedbrake";
    this->simArr[brake_parking] = "/sim/model/c172p/brake-parking";
    this->simArr[engine_primer] = "/controls/engines/engine/primer";
    this->simArr[engine_mixture] = "/controls/engines/current-engine/mixture";
    this->simArr[master_bat] = "/controls/switches/master-bat";
    this->simArr[master_alt] = "/controls/switches/master-alt";
    this->simArr[engine_rpm] = "/engines/engine/rpm";
    }