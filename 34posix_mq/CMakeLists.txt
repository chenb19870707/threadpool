cmake_minimum_required(VERSION 2.8.0)

 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Wno-unused-variable -pthread")


ADD_EXECUTABLE(01mq_open 01mq_open.cpp)
ADD_EXECUTABLE(02mq_unlink 02mq_unlink.cpp)
ADD_EXECUTABLE(03mq_getattr 03mq_getattr.cpp)
ADD_EXECUTABLE(04mq_send 04mq_send.cpp)
ADD_EXECUTABLE(05mq_recv 05mq_recv.cpp)
ADD_EXECUTABLE(06mq_notify 06mq_notify.cpp)


TARGET_LINK_LIBRARIES(01mq_open rt)
TARGET_LINK_LIBRARIES(02mq_unlink rt)
TARGET_LINK_LIBRARIES(03mq_getattr rt)
TARGET_LINK_LIBRARIES(04mq_send rt)
TARGET_LINK_LIBRARIES(05mq_recv rt)
TARGET_LINK_LIBRARIES(06mq_notify rt)