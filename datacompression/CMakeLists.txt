cmake_minimum_required(VERSION 3.9)
project(datacompression)

set(CMAKE_CXX_STANDARD 11)

add_executable(datacompression main/main.cpp entropy/Entropy.cpp entropy/Entropy.h huffman/Huffman.cpp huffman/Huffman.h)