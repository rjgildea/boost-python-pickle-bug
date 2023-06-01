cmake_minimum_required(VERSION 3.15)
project(boost-python-pickle-bug)

# Find python and Boost - both are required dependencies
find_package(Python REQUIRED COMPONENTS Development)
find_package(Boost REQUIRED COMPONENTS "python${Python_VERSION_MAJOR}${Python_VERSION_MINOR}")

Python_add_library(greeting_ext MODULE greeting.cpp)
target_link_libraries(greeting_ext PRIVATE "Boost::python${Python_VERSION_MAJOR}${Python_VERSION_MINOR}")

