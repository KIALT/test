#pragma once

#include "noncopy.h"
#include "taos_option.h"
#include <cstdint>
#include <functional>
#include <memory>
#include <stdint.h>
#include <string>
#include <string_view>
#include <taos.h>

class TAOSValue
{
public:
    TAOSValue(void *value);
    ~TAOSValue() = default;

    void            *Get() const { return value_; }
    int8_t           AsInt8() const { return *(int8_t *) value_; }
    uint8_t          AsUInt8() const { return *(uint8_t *) value_; }
    int16_t          AsInt16() const { return *(int16_t *) value_; }
    uint16_t         AsUInt16() const { return *(uint16_t *) value_; }
    int32_t          AsInt32() const { return *(int32_t *) value_; }
    uint32_t         AsUInt32() const { return *(uint32_t *) value_; }
    int64_t          AsInt64() const { return *(int64_t *) value_; }
    uint64_t         AsUInt64() const { return *(uint64_t *) value_; }
    float            AsFloat() const { return *(float *) value_; }
    double           AsDouble() const { return *(double *) value_; }
    std::string      AsString() const { return std::string(static_cast<char *>(value_)); }
    std::string_view AsStringView() const { return std::string_view(static_cast<char *>(value_)); }
    std::string      AsTimestamp() const;

private:
    void *value_;
};

class TAOSRow
{
public:
    TAOSRow() : row_(nullptr) {}
    explicit TAOSRow(TAOS_ROW row) : row_(row) {}
    ~TAOSRow() = default;

    bool      IsNil() const { return row_ == nullptr; }
    bool      operator==(const TAOSRow &other) const { return row_ == other.row_; }
    bool      operator!=(const TAOSRow &other) const { return row_ != other.row_; }
    TAOSValue operator[](size_t index) const { return TAOSValue(row_[index]); }

private:
    TAOS_ROW row_;
};

class TAOSResult : public NonCopyable
{
public:
    class Iterator
    {
    public:
        Iterator(TAOS_RES *res, const TAOSRow &row) : res_(res), row_(row) {}
        virtual ~Iterator() = default;

        bool      operator==(const Iterator &other) const { return row_ == other.row_; }
        bool      operator!=(const Iterator &other) const { return row_ != other.row_; }
        TAOSRow   operator*() const { return row_; }
        Iterator &operator++() {
            row_ = TAOSRow(taos_fetch_row(res_));
            return *this;
        }

    private:
        TAOS_RES *res_;
        TAOSRow   row_;
    };

    TAOSResult(TAOS_RES *res);
    ~TAOSResult() = default;

    TAOSResult(TAOSResult &&other) noexcept;
    TAOSResult &operator=(TAOSResult &&other) noexcept;
    bool        IsNil() const { return res_ == nullptr; }
    size_t      FieldCount() const { return taos_field_count(res_.get()); }
    TAOSRow     NextRow() const { return TAOSRow(taos_fetch_row(res_.get())); }
    Iterator    begin() const { return Iterator(res_.get(), TAOSRow(taos_fetch_row(res_.get()))); }
    Iterator    end() const { return Iterator(res_.get(), TAOSRow()); }

private:
    std::unique_ptr<TAOS_RES, std::function<void(TAOS_RES *)>> res_;
};
