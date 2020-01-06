//
// Created by yuvallevy on 20/12/2019.
//

#include "SleepCommand.h"
#include <vector>
#include <string>
#include <thread>
using namespace std;

// makes the thread who called the func go to sleep.
int SleepCommand:: execute(vector<vector<string>> arr, int index){
    int mili;
    Interpreter interpreter;
    try{
        mili = (int) interpreter.interpret(arr[index][1])->calculate();
    }catch(char* err) {
        mili = 5400;
    } catch(exception* ex){
        mili = 5400;
    }

    this_thread::sleep_for(std::chrono::milliseconds(mili));
    return 1;
}
// constructor.
SleepCommand:: SleepCommand() : Command() {

}

//    ~SleepCommand()= default;