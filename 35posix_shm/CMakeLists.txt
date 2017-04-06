cmake_minimum_required(VERSION 2.8.0)

 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Wno-unused-variable -pthread")


ADD_EXECUTABLE(01shm_open 01shm_open.cpp)
ADD_EXECUTABLE(02ftruncate 02ftruncate.cpp)
ADD_EXECUTABLE(03shm_unlink 03shm_unlink.cpp)
ADD_EXECUTABLE(04mmap 04mmap.cpp)
ADD_EXECUTABLE(05shm_read 05shm_read.cpp)


TARGET_LINK_LIBRARIES(01shm_open rt)
TARGET_LINK_LIBRARIES(02ftruncate rt)
TARGET_LINK_LIBRARIES(03shm_unlink rt)
TARGET_LINK_LIBRARIES(04mmap rt)
TARGET_LINK_LIBRARIES(05shm_read rt)