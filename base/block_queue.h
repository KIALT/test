#pragma once

#include "noncopy.h"
#include <condition_variable>
#include <mutex>
#include <optional>
#include <queue>

template<typename T>
class BlockQueue : public NonCopyable
{
public:
    BlockQueue() = default;
    ~BlockQueue() { Stop(); }

    void Enqueue(const T &item) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!running_) {
            return;
        }
        queue_.push(item);
        cv_.notify_one();
    }

    void Enqueue(T &&item) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!running_) {
            return;
        }
        queue_.push(std::move(item));
        cv_.notify_one();
    }

    T Dequeue() {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this]() { return !queue_.empty() || !running_; });
        if (!running_ && queue_.empty()) {
            return T();
        }
        T item = std::move(queue_.front());
        queue_.pop();
        return item;
    }

    std::optional<T> TryDequeue() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (queue_.empty()) {
            return std::nullopt;
        }
        T item = std::move(queue_.front());
        queue_.pop();
        return item;
    }

    std::optional<T> WaitDequeue(int timeout_ms) {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait_for(lock, std::chrono::milliseconds(timeout_ms), [this]() { return !queue_.empty() || !running_; });
        return TryDequeue();
    }

    void Stop() {
        std::lock_guard<std::mutex> lock(mutex_);
        running_ = false;
        cv_.notify_all();
    }

protected:
    mutable std::mutex      mutex_;
    std::condition_variable cv_;
    std::queue<T>           queue_;
    bool                    running_ = true;
};
