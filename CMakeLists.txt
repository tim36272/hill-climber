cmake_minimum_required(VERSION 2.8)
project( valueFinder C CXX)

set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_ADDITIONAL_VERSIONS "1.48" "1.46")

find_package( Boost REQUIRED COMPONENTS thread )
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-o ../f11 ../f11.o")


add_executable( main main.cpp )
target_link_libraries( main ${Boost_LIBRARIES} )
