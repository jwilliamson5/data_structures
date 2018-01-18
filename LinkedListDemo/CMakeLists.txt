cmake_minimum_required(VERSION 3.9)
project(LinkedListDemo)

set(CMAKE_CXX_STANDARD 11)

add_executable(LinkedListDemo LinkedList.cpp llist.cpp llist.h node.cpp node.h)