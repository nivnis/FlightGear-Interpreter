//
// Created by pikachu on 12/23/19.
//

#ifndef PORJECT1_SERVER_H
#define PORJECT1_SERVER_H
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>
#include <vector>
#include <thread>
#pragma once
using namespace std;

class Server {
private:
    int port;
    int client_socket;
    string simArr[36];
    //makes an array of sims by xml order
    void makeSimArray();
    //makes a vector of values by xml order
    static vector<float> getValVector(string s);
public:
    Server(int portNumber);
    //opens a thread that runs on runServer() function
    void runServerThread();
    //gets data from the simulator to the server
    void runServer();
};

enum vars {
    airspeed = 0,
    warp,
    magnetos,
    heading,
    alt,
    pressure,
    pitch,
    roll,
    internal_pitch,
    internal_roll,
    encoder_alt,
    encoder_pressure,
    gps_alt,
    gps_ground_speed,
    gps_vertical_speed,
    indicated_heading,
    compass,
    slip_skid,
    turn_rate,
    indicated_speed,
    aileron,
    elevator,
    rudder,
    flaps,
    engine_throttle,
    curr_engine_throttle,
    master_avionics,
    starter,
    auto_start,
    speedbrake,
    brake_parking,
    engine_primer,
    engine_mixture,
    master_bat,
    master_alt,
    engine_rpm
};

#endif //PORJECT1_SERVER_H
