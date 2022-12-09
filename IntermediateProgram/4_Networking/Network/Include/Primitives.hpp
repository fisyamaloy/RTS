#pragma once

#include <Utility/Utility.hpp>
#include <chrono>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

struct FileInfo
{
    std::size_t  size;
    std::string  name;
    std::wstring text;

    FileInfo() = default;

    FileInfo(const std::size_t size, std::string name, std::wstring text)
        : size(size), name(std::move(name)), text(std::move(text))
    {
    }
    FileInfo(const FileInfo& other) : size(other.size), name(other.name), text(other.text) {}
    ~FileInfo() = default;
    FileInfo(FileInfo&& other)
        : size(std::move(other.size)), name(std::move(other.name)), text(std::move(other.text))
    {
    }

    friend bool operator==(const FileInfo& first, const FileInfo& second)
    {
        return first.size == second.size && first.name == second.name && first.text == second.text;
    }
};

/// Serialize method which serialize each field
template <typename Archive>
void serialize(Archive& ar, FileInfo& o)
{
    ar& o.size& o.name& o.text;
}
