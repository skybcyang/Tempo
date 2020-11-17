//
// Created by skybcyang on 2020/11/15.
//

#include <iostream>
#include <queue>
#include <mutex>
#include "../third_party/catch.hpp"

template <typename TUPLE>
class DataCenterT {
public:
    DataCenterT& GetDataCenterIns() {
        static DataCenterT dataCenter;
        return dataCenter;
    }
    constexpr static size_t tuple_size = std::tuple_size_v<std::decay<TUPLE>>;
    static bool slide_window_flag[tuple_size];
};








TEST_CASE("test model2") {

}