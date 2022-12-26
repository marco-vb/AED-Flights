cmake_minimum_required(VERSION 3.23)
project(flights)

set(CMAKE_CXX_STANDARD 17)

add_executable(flights main.cpp Airport.cpp Airport.h graph.cpp graph.h haversine.cpp Airline.cpp Airline.h)
