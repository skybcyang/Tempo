cmake_minimum_required(VERSION 3.17)
project(Tempo)

set(CMAKE_CXX_STANDARD 17)

add_executable(Tempo input_multi_stream_and_sync_model.cpp input_multi_stream_and_sync_model2.cpp catch.cpp third_party/catch.hpp)
