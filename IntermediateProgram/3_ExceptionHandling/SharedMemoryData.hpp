#pragma once
#include <iostream>
#include <string>
#include <boost/serialization/string.hpp>

struct SharedMemoryData
{
    std::string buffer;
    bool        finish;
    SharedMemoryData() : finish(false)
    {
        std::cout << "SharedMemoryData()\n";
    }
    SharedMemoryData(char* buffer, bool isFinish) : buffer(buffer), finish(isFinish)
    {
        std::cout << "SharedMemoryData(char* buffer, bool isFinish)\n";
    }
    ~SharedMemoryData()
    {
        std::cout << "~SharedMemoryData()\n";
    }

    inline bool isFinished() const
    {
        return finish;
    }

    friend class boost::serialization::access;

private:
    template <class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        (version);
        ar& finish;
        ar& buffer;
    }
};
