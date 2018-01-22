cmake_minimum_required(VERSION 3.9)
project(entropy)

set(CMAKE_CXX_STANDARD 11)

add_executable(entropy main.cpp Entropy.cpp Entropy.h)