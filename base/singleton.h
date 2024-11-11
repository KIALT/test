#pragma once

#include "noncopy.h"
#include <mutex>

template<typename T>
class Singleton : private NonCopyable
{
public:
    static T &Instance() {
        std::call_once(once_flag_, []() { instance_ = new T(); });
        return *instance_;
    }

protected:
    Singleton()          = default;
    virtual ~Singleton() = default;

private:
    static T             *instance_;
    static std::once_flag once_flag_;
};

template<typename T>
T *Singleton<T>::instance_ = nullptr;

template<typename T>
std::once_flag Singleton<T>::once_flag_;
