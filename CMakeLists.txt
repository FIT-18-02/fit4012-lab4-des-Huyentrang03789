cmake_minimum_required(VERSION 3.10)
project(fit4012_lab4_des LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(des des.cpp)

target_compile_options(des PRIVATE -Wall -Wextra -pedantic)
