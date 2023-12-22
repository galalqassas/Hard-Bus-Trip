cmake_minimum_required(VERSION 3.24)
project(easy_bus_trip_v2)

set(CMAKE_CXX_STANDARD 17)

add_executable(easy_bus_trip_v2 main.cpp Company.cpp Event.cpp LeaveEvent.cpp LinkedList.cpp NpPassengerQueue.cpp Passenger.cpp PriorityQueue.cpp Queue.cpp Station.cpp Time.cpp)
