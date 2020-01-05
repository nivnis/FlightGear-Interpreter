//
// Created by yuvallevy on 20/12/2019.
//

#include "SleepCommand.h"
#include <vector>
#include <iostream>
#include <string>
#include <thread>
using namespace std;

// makes the thread who called the func go to sleep.
int SleepCommand:: execute(vector<vector<string>> arr, int index){
    int mili = stol(arr[index][1]);
    this_thread::sleep_for(std::chrono::milliseconds(mili));
    return 1;
}
// constructor.
SleepCommand:: SleepCommand() : Command() {

}

//    ~SleepCommand()= default;