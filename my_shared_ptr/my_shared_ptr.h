//
// Created by skybcyang on 2020/11/25.
//

#ifndef TEMPO_MY_SHARED_PTR_H
#define TEMPO_MY_SHARED_PTR_H

#include <iostream>

struct UserCount {
public:
    UserCount() : user_count(new size_t(1)) {}
    UserCount(const UserCount& uc) : user_count(uc.user_count) {
        ++(*user_count);
    }
    ~UserCount() {
        if (--(*user_count) == 0) {
            delete user_count;
        }
    }

    bool Only() {
        return *user_count == 1;
    }
    bool reattach(const UserCount& uc) {
        ++(*uc.user_count);
        if (--(*user_count) == 0) {
            delete user_count;
            user_count = uc.user_count;
            return true;
        }
        user_count = uc.user_count;
        return false;
    }
    size_t GetUserCount() {
        return *user_count;
    }

private:
    UserCount& operator=(const UserCount& uc);
private:
    size_t* user_count;
};

template <typename T>
struct MySharedPtr {
public:
    MySharedPtr() : t(new T) {}
    template<typename ...Ts>
    MySharedPtr(Ts... args) : t(new T(args...)) {}
    MySharedPtr(const MySharedPtr& rhs) : t(rhs.t), uc(rhs.uc) {}
    MySharedPtr(const T& tt) : t(new T(tt)) {}
    MySharedPtr& operator=(const MySharedPtr& rhs) {
        if (uc.reattach(rhs.uc)) {
            delete t;
        }
        t = rhs.t;
        return *this;
    }
    ~MySharedPtr() {
        if (uc.Only()) {
            delete t;
        }
    }
    T* Get() { return t; }
    size_t GetUserCount() { return uc.GetUserCount(); }
private:
    T* t;
    UserCount uc;
};


template <typename T, typename ...Ts>
MySharedPtr<T> make_shared(Ts... args) {
    return MySharedPtr<T>(args...);
}

#endif //TEMPO_MY_SHARED_PTR_H
