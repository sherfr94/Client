cmake_minimum_required(VERSION 3.8)
project(Client)

message(STATUS "start running cmake...")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 ")
#set(Boost_INCLUDE_DIR "boost_1_61_0")
#set(Boost_LIBRARY_DIR "boost_1_61_0/libs/")

set(BOOST_ROOT "boost_1_58_0")

find_package(Boost 1.58.0 COMPONENTS filesystem system thread REQUIRED)

if(Boost_FOUND)

LINK_DIRECTORIES(${Boost_LIBRARY_DIR})

message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
message(STATUS "Boost_VERSION: ${Boost_VERSION}")

include_directories(${Boost_INCLUDE_DIRS})

endif()

add_executable(Client
        src/connectionHandler.cpp include/connectionHandler.h
        src/echoClient.cpp
        src/KeyboardThread.cpp src/KeyboardThread.h)

if(Boost_FOUND)
target_link_libraries(Client ${Boost_LIBRARIES})

endif()