//
// Created by skybcyang on 2020/11/25.
//

#include "my_shared_ptr.h"
#include "../third_party/catch.hpp"

class Data {
public:
    Data() {}
    Data(int x, double y) : i(x), d(y) {}
    int GetI() {
        return i;
    }
    double GetD() {
        return d;
    }
private:
    int i;
    double d;
};


TEST_CASE("Test My Shared Ptr") {
    MySharedPtr<Data> data{1,2.22};
    REQUIRE(data.Get()->GetI() == 1);
    REQUIRE(data.Get()->GetD() == 2.22);
}