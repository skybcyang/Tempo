//
// Created by skybcyang on 2020/12/23.
//

#include "../third_party/catch.hpp"

#include <iostream>
#include <tuple>


template <typename T, typename F, size_t ...Ts>
void ForEach(T&& t, F&& f, std::index_sequence<Ts...>) {
    (f(std::get<Ts>(t)), ...);
}

template <typename T, typename F, size_t ...Ts>
void ForEach(T&& t, F&& f) {
    ForEach(std::forward<T>(t), std::forward<F>(f), std::make_index_sequence<std::tuple_size_v<std::decay_t<T>>>());
}

template <typename Tuple>
void Print(Tuple&& tuple) {
    ForEach(tuple, [](auto value) {std::cout << value << std::endl;});
}


TEST_CASE("test tuple for each") {
    std::tuple<int, double, std::string> t {1, 2.3, "hello, Ts..."};
    Print(t);
}