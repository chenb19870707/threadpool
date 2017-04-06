cmake_minimum_required(VERSION 2.8.0)

 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Wno-unused-variable -pthread")

ADD_EXECUTABLE(nofile_limit nofile_limit.cpp)
ADD_EXECUTABLE(echocli echocli.cpp)
ADD_EXECUTABLE(stresscli stresscli.cpp)
ADD_EXECUTABLE(echosvr echosvr.cpp)
ADD_EXECUTABLE(pollsvr echosvr.cpp)