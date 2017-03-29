cmake_minimum_required(VERSION 3.6)
project(Homework)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(bigint
        Bigint/main.cpp
        Bigint/BigInt.cpp
        Bigint/BigInt.h)

add_executable(Rational
        Rational/main.cpp
        Rational/Rational.cpp
        Rational/Rational.h)