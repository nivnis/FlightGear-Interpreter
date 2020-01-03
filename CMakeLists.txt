cmake_minimum_required(VERSION 3.15)
project(Porject1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(Porject1 main.cpp Server.cpp Server.h Client.cpp Client.h Command.h ConditionParser.h ConnectCommand.cpp
        ConnectCommand.h DefineVarCommand.cpp DefineVarCommand.h ex1.cpp ex1.h IfCommand.cpp IfCommand.h
        OpenServerCommand.cpp OpenServerCommand.h PrintCommand.cpp PrintCommand.h SleepCommand.cpp SleepCommand.h
        SymbolTable.cpp SymbolTable.h Var.cpp Var.h WhileCommand.cpp WhileCommand.h Parser.cpp Parser.h)