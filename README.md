# FlightGear Interpreter

This is a code that controls the plane inside the FlightGear flight simulator virtual space.

In this project we:
```bash
1) Connecting the simulator via TCP/IP connection protocol.
2) Sending commands to the plane and fly it.
```

## Details
We fly the plane inside the simulator with our pre-written code. We use our lexer and parser and interpret the code.
our interpreter works in two directions:

1. Receives data from the simulator as a **server** and updates the program's older data with the new values it received. The simulator sends us the values we ask him to send us in the **generic_small.xml** file (more about the xml file in Installation below).
2. Sends data as a **client** to the simulator to correctly maneuver the plane according to the commands listed in fly.txt.

## Installation
We used FlightGear in Linux. 
1. The installation is executed by the command:
	```bash
	sudo apt-get install flightgear
	```
2. The TCP protocol xml file:  **generic_small.xml** should be added to the /data/Protocol directory of the game. You can find the file in this repository.
3. We must define the connection inside the simulator's settings under "additional settings":
	```bash
	--telnet=socket,in,10,127.0.0.1,5402,tcp // connection
	--generic=socket,out,10,127.0.0.1,5400,tcp,generic_small // makes the simulator know it needs to send us the data according to the xml file.
	```
Here is how it should look like:
![Additional Settings](https://github.com/nivnis/ex3/blob/master/Capture.JPG?raw=true)
## Compiling

Everything you need is right here in this repository.
just run the following command:
```bash
	g++ -std=c++11 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread
```
## Running

The interpreter receives a single argument which is the path of the text file that contains all the code we will want to run.
After compiling - execute the program by writing the next commands:
1. ```bash
	./a.out fly.txt
	```
	This will run the fly.txt file.
2. ```bash
	./a.out your_file_name.txt
	```
	This will run the file you want to insert to the program.
	
After running the program - enter FlightGear and click on FLY!
The code will make the plane take off and fly.
## Syntax

Notice the following restrictions:
1. Conditions cannot be used inside a while loop.
2. Conditions can only contain a single boolean expression.
3. There must be '()' after a minus when writting an expression.
4. There are no '()' in the conditions (if,while).

Other than thay the code is very intuitive. You may have a better idea about the syntax after taking a look at the fly.txt file.
