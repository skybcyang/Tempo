//
// Created by skybcyang on 2020/11/15.
//

#include <iostream>
#include <queue>
#include <mutex>
#include "third_party/catch.hpp"

using DeviceId = int32_t;

enum CameId : uint32_t {
    cam0,
    cam1,
    cam2,
    cam3
};

template <DeviceId deviceId, typename T>
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

using cam0stream = DataQueue<cam0, int>;
using cam1stream = DataQueue<cam1, float>;
using cam2stream = DataQueue<cam2, std::string>;
using cam3stream = DataQueue<cam3, int>;

struct DataSet {
    int a;
    float b;
    std::string c;
    int d;
};


template <typename T, typename F, size_t ...Is>
void foreach(T&& tuple, F&& f, std::index_sequence<Is...>) {
    (
        (
            f(std::get<Is>(tuple))
        ), ...
    );
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
class DataSet : public TUPLE {
public:
    void Sync() {
        foreach(static_cast<TUPLE&>(*this), [](auto& value) -> Data{std::cout<<value.GetAndPopData()<<std::endl;});
    }
    template <typename T>
    T& GetDataQueue() {
        return std::get<T>(static_cast<TUPLE&>(*this));
    }
};

using DataSetInstance = DataSet<std::tuple<cam0stream, cam1stream, cam2stream, cam3stream>>;



TEST_CASE("an empty list appends an non-empty task list") {
    DataSetInstance dataset;
    dataset.GetDataQueue<cam0stream>().PushData(1);
    dataset.GetDataQueue<cam1stream>().PushData(3.2);
    dataset.GetDataQueue<cam2stream>().PushData("ssdsds");
    dataset.GetDataQueue<cam3stream>().PushData(9);
    auto data = dataset.Sync();
}
