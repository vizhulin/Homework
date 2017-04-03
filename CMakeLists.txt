cmake_minimum_required(VERSION 3.6)
project(Homework)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(bigint
        Bigint/main.cpp
        Bigint/BigInt.cpp
        Bigint/BigInt.h)

add_executable(Rational
        Rational/main.cpp
        )

add_executable(Geometry
        Geometry/main.cpp
        Geometry/geometry.cpp
        Geometry/geometry.h)

add_executable(Matrix
        Matrix/main.cpp
        )