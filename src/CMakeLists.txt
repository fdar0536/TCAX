cmake_minimum_required(VERSION 3.14.0)
project(TCAX CXX C)
set(CMAKE_CXX_STANDARD 14)

message("cmake cxx compiler is ${CMAKE_CXX_COMPILER}")
set(CMAKE_CXX_FLAGS "-Wl,--unresolved-symbols=report-all -Wall -Wextra -Werror -Wno-enum-compare -Wno-sign-compare -Wno-int-to-pointer-cast")
set(CMAKE_C_FLAGS "-Wl,--unresolved-symbols=report-all -Wall -Wextra -Werror -Wno-sign-compare -Wno-int-to-pointer-cast")

#boost
find_package(Boost 1.69.0 REQUIRED COMPONENTS python3 locale)

#python
find_package(Python 3.7 REQUIRED COMPONENTS Development)

#freetype2
find_package(Freetype 2.9 REQUIRED)

add_subdirectory(tcaxLib)
add_subdirectory(tcax)