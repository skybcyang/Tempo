//
// Created by skybcyang on 2020/11/15.
//

#include <iostream>
#include <queue>
#include <mutex>
#include "third_party/catch.hpp"

template <typename T>
class DataQueue{
public:
    void PushData(T data) {
        std::lock_guard<std::mutex> lock(mtx);
        dataqueue.push(data);
    }
    T GetAndPopData() {
        if (dataqueue.size()>0) {
            while(dataqueue.size()==0){
                //
            }
        }
        std::lock_guard<std::mutex> lock(mtx);
        auto data = dataqueue.front();
        dataqueue.pop();
        return data;
    }
private:
    std::mutex mtx;
    std::queue<T> dataqueue;
};

using cam0stream = DataQueue<int>;
using cam1stream = DataQueue<float>;
using cam2stream = DataQueue<std::string>;

struct DataSet {
    int a;
    float b;
    std::string c;
    void SetValue(int v){
        a = v;
    }
    void SetValue(float v){
        b = v;
    }
    void SetValue(std::string v){
        c = v;
    }
};

template <typename T, typename F, size_t ...Is>
void foreach(T&& tuple, F&& f, std::index_sequence<Is...>) {
    ((f(std::get<Is>(tuple))), ...);
}

template <typename T, typename F>
void foreach(T&& tuple, F&& f) {
    foreach(
            std::forward<T>(tuple),
            std::forward<F>(f),
            std::make_index_sequence<std::tuple_size_v<std::decay_t<T>>>{}
    );
}

template <typename TUPLE>
class DataCenterT : public TUPLE {
public:
    auto SyncData() -> DataSet {
        DataSet dataSet;
        foreach(static_cast<TUPLE&>(*this), [&](auto& value){dataSet.SetValue(value.GetAndPopData());});
        return dataSet;
    }
    template <typename T>
    T& GetDataQueue() {
        return std::get<T>(static_cast<TUPLE&>(*this));
    }
};

using DataCenter = DataCenterT<std::tuple<cam0stream, cam1stream, cam2stream>>;


TEST_CASE("test sync") {
    DataCenter dataCenter;
    dataCenter.GetDataQueue<cam0stream>().PushData(1);
    dataCenter.GetDataQueue<cam1stream>().PushData(5.20);
    dataCenter.GetDataQueue<cam2stream>().PushData("sky");

    auto dataSet = dataCenter.SyncData();
    REQUIRE(dataSet.a == 1);
    REQUIRE(dataSet.b == 5.2f);
    REQUIRE(dataSet.c == "sky");
}