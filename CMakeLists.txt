cmake_minimum_required(VERSION 3.17)
project(Tempo)

set(CMAKE_CXX_STANDARD 17)

add_executable(Tempo
        multi_stream_input_and_sync/model1.cpp
        multi_stream_input_and_sync/model2.cpp
        catch.cpp
        third_party/catch.hpp
        )
