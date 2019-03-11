cmake_minimum_required(VERSION 3.11.4)
set(ENABLE_ENET  ON  CACHE BOOL "Adds Networking to the Project" FORCE)
include(CMake/enetpp.cmake)
add_subdirectory(Client)
add_subdirectory(Server)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0" )