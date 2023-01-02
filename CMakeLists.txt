cmake_minimum_required(VERSION 3.23)
project(flights)

set(CMAKE_CXX_STANDARD 17)

add_executable(flights test.cpp Airport.cpp Airport.h graph.cpp graph.h haversine.cpp haversine.h Airline.cpp Airline.h Coord2dTree.cpp Coord2dTree.h Rect.cpp Rect.h coordinates.cpp coordinates.h)
