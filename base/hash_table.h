#pragma once

#include <cstddef>
#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>

struct HashEntry {
    std::string key;
    std::string field;

    HashEntry() = default;
    HashEntry(const std::string &k, const std::string &f) : key(k), field(f) {}

    bool operator==(const HashEntry &rhs) const { return key == rhs.key && field == rhs.field; }
};

namespace std {
template<>
struct hash<HashEntry> {
    size_t operator()(const HashEntry &entry) const {
        return std::hash<std::string>()(entry.key) ^ (std::hash<std::string>()(entry.field) << 1);
    }
};
}// namespace std

template<typename T>
class HashTable
{
public:
    HashTable()  = default;
    ~HashTable() = default;

    void Put(const HashEntry &entry, const T &value) {
        std::lock_guard<std::mutex> guard(mutex_);
        table_[entry] = value;
    }

    std::optional<T> Get(const HashEntry &entry) const {
        std::lock_guard<std::mutex> guard(mutex_);
        auto                        it = table_.find(entry);
        if (it != table_.end()) {
            return it->second;
        }
        return std::nullopt;
    }

    void Del(const HashEntry &entry) {
        std::lock_guard<std::mutex> guard(mutex_);
        table_.erase(entry);
    }

private:
    mutable std::mutex               mutex_;
    std::unordered_map<HashEntry, T> table_;
};
