#pragma once

#include <optional>
#include <string>
#include <variant>

template<typename T, typename E>
class Result
{
public:
    Result(const T &value) : value_(value) {}
    Result() : value_() {}
    Result(const E &error) : value_(error) {}

    bool     IsOk() const { return std::holds_alternative<T>(value_); }
    bool     IsErr() const { return std::holds_alternative<E>(value_); }
    T       &Unwrap() { return std::get<T>(value_); }
    E       &UnwrapErr() { return std::get<E>(value_); }
    const T &Unwrap() const { return std::get<T>(value_); }
    const E &UnwrapErr() const { return std::get<E>(value_); }

private:
    std::variant<T, E> value_;
};

template<typename T, typename E>
Result<T, E> Ok(const T &value) {
    return Result<T, E>(value);
}

template<typename T, typename E>
Result<T, E> Err(const E &error) {
    return Result<T, E>(error);
}

template<typename T>
class ResultOr
{
public:
    ResultOr(const T &value) : value_(value) {}
    ResultOr(T &&value) : value_(std::move(value)) {}
    ResultOr(const std::nullopt_t &) : value_(std::nullopt) {}

    bool               IsOk() const { return value_.has_value(); }
    bool               IsErr() const { return !value_.has_value(); }
                       operator bool() const { return value_.has_value(); }
    T                 &operator*() { return value_.value(); }
    const T           &operator*() const { return value_.value(); }
    T                 &value() { return value_.value(); }
    const T           &value() const { return value_.value(); }
    std::string       &error() { return error_; }
    const std::string &error() const { return error_; }

    static ResultOr<T> Ok(const T &value) { return ResultOr<T>(value); }
    static ResultOr<T> Err(const std::string &error) { return ResultOr<T>(std::nullopt, error); }

private:
    std::optional<T> value_;
    std::string      error_;
};
