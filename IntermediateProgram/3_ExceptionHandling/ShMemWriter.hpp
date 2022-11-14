#pragma once
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include <memory>
#include <string>
#include <sstream>

#include "SharedMemoryData.hpp"

using boost::interprocess::create_only;

class ShMemWriter
{
public:
    ShMemWriter(const std::string& shMemName, const boost::ulong_long_type maxMessages,
        const boost::ulong_long_type messageSize)
        : _shMemName(shMemName)
    {
        _messages = std::make_unique<boost::interprocess::message_queue>(
            create_only, _shMemName.c_str(), maxMessages, messageSize);
    }
    ShMemWriter(ShMemWriter&) = delete;

    ~ShMemWriter() = default;

    void write(const SharedMemoryData& shMemBuf) 
    {
        std::stringstream             oss;
        boost::archive::text_oarchive oa(oss);
        oa << shMemBuf;
        std::string serialized_string(oss.str());

        _messages->send(serialized_string.data(), serialized_string.size(), 0);
    }

private:
    std::string _shMemName;
    std::unique_ptr<boost::interprocess::message_queue> _messages;
};
