cmake_minimum_required(VERSION 3.17)
project(Tempo)

set(CMAKE_CXX_STANDARD 17)

add_executable(Tempo
        multi_stream_input_and_sync/model.cpp
        catch.cpp
        third_party/catch.hpp
        my_shared_ptr/my_shared_ptr.h my_shared_ptr/test_my_shared_ptr.cpp tuple_for_each/tuple_for_each.cpp static_reflection/static_reflection.cpp)
