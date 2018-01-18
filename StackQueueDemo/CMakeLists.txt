cmake_minimum_required(VERSION 3.9)
project(StackQueueDemo)

set(CMAKE_CXX_STANDARD 11)

add_executable(StackQueueDemo
        LinkedQueues.cpp
        stack.cpp
        stack.h
        stacknode.cpp
        stacknode.h
        Stacks.cpp)
