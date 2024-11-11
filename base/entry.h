#pragma once

#include <string>
#include <string_view>
#include <vector>

template<typename T>
struct Entry {
    std::string group; /* 数据组名 */
    std::string tag;   /* 数据标签 */
    std::string meta;  /* 数据元信息 */
    T           value; /* 数据值 */

    Entry(const std::string_view group, const std::string_view tag) : group(group), tag(tag) {}

    bool operator==(const Entry &other) const {
        return group == other.group && tag == other.tag && meta == other.meta && value == other.value;
    }

    bool operator<(const Entry &other) const {
        return group < other.group || (group == other.group && tag < other.tag);
    }
};

template<typename T>
struct MultiEntry {
    std::string           group;   /* 数据组名 */
    std::vector<Entry<T>> entries; /* 数据项 */

    MultiEntry(std::string group, std::vector<Entry<T>> entries = {}) : group(group), entries(entries) {}

    void                     AddEntry(const Entry<T> &entry) { entries.push_back(entry); }
    std::vector<std::string> GetEntryTags() const {
        std::vector<std::string> tags;
        for (const auto &entry: entries) {
            tags.push_back(entry.tag);
        }
        return tags;
    }

    bool operator==(const MultiEntry &other) const { return group == other.group && entries == other.entries; }
    bool operator<(const MultiEntry &other) const { return group < other.group; }
};
