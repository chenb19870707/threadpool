cmake_minimum_required(VERSION 2.8.0)

 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Wno-unused-variable -pthread")


ADD_EXECUTABLE(01thread 01thread.cpp)
TARGET_LINK_LIBRARIES(01thread pthread)

ADD_EXECUTABLE(echosvr echosvr.cpp)
TARGET_LINK_LIBRARIES(echosvr pthread)

ADD_EXECUTABLE(echocli echocli.cpp)
TARGET_LINK_LIBRARIES(echocli pthread)