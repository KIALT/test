#pragma once

#include "noncopy.h"

#include <atomic>
#include <functional>
#include <type_traits>

class Deferred : public NonCopyable
{
public:
    Deferred() = default;
    template<class F, class = std::enable_if_t<std::is_invocable_v<F>>>
    explicit Deferred(F &&f) : action_(std::forward<F>(f)) {}

    ~Deferred() { Call(); }
    void Reset() { action_ = nullptr; }
         operator bool() const noexcept { return action_ != nullptr; }

private:
    std::function<void()> action_;

    void Call() {
        if (action_) {
            action_();
        }
    }
};
