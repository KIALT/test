#pragma once

#include <atomic>
#include <condition_variable>
#include <mutex>

class LightSignal
{
public:
    LightSignal()  = default;
    ~LightSignal() = default;

    void Notify() {
        std::lock_guard<std::mutex> lock(mutex_);
        flag_.store(true, std::memory_order_relaxed);
        cv_.notify_all();
    }

    void Wait() {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this]() { return flag_.load(std::memory_order_relaxed); });
    }

    void WaitFor(std::chrono::milliseconds ms) {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait_for(lock, ms, [this]() { return flag_.load(std::memory_order_relaxed); });
    }

    bool WaitFor(std::chrono::milliseconds ms, bool &result) {
        std::unique_lock<std::mutex> lock(mutex_);
        return cv_.wait_for(lock, ms, [this]() { return flag_.load(std::memory_order_relaxed); });
    }

    void Reset() { flag_.store(false, std::memory_order_relaxed); }

private:
    std::atomic_bool        flag_{false};
    std::mutex              mutex_;
    std::condition_variable cv_;
};
