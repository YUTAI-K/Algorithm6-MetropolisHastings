cmake_minimum_required(VERSION 3.27)
project(Algorithm6)

set(CMAKE_CXX_STANDARD 20)

add_executable(Algorithm6 src/main.cpp
        src/Algorithm6.h
        src/import.h
        src/export.h
        src/generate_samples.h
        src/Algorithm6.cpp
        src/generate_samples.cpp)
