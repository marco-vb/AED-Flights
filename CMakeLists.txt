cmake_minimum_required(VERSION 3.23)
project(flights)

set(CMAKE_CXX_STANDARD 17)

add_executable(flights main.cpp HelperClasses/Airport.cpp HelperClasses/Airport.h DataStructures/Graph.cpp DataStructures/Graph.h HelperClasses/Haversine.cpp HelperClasses/Haversine.h HelperClasses/Airline.cpp HelperClasses/Airline.h DataStructures/Coord2dTree.cpp DataStructures/Coord2dTree.h HelperClasses/Rect.cpp HelperClasses/Rect.h)
