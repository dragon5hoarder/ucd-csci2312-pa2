cmake_minimum_required(VERSION 3.3)
project(PA3_Int)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Point.h Cluster.h KMeans.h Exceptions.cpp Exceptions.h)
add_executable(PA3_Int ${SOURCE_FILES})