#pragma once
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include <memory>
#include <string>
#include <sstream>

#include "SharedMemoryData.hpp"

using boost::interprocess::open_only;

class ShMemReader
{
public:
    ShMemReader(const std::string& shMemName) : _shMemName(shMemName)
    {
        try
        {
            _messages =
                std::make_unique<boost::interprocess::message_queue>(open_only, _shMemName.c_str());
        }
        catch (boost::interprocess::interprocess_exception& e)
        {
            std::cerr << e.what() << std::endl; 
        }
    }

    ~ShMemReader() 
    {
        boost::interprocess::message_queue::remove(_shMemName.c_str());
    }

    SharedMemoryData read(const size_t bufferSize) 
    {
        static boost::ulong_long_type recievedSize = 0;
        static unsigned int           priority     = 0;

        std::string serialized_string;
        serialized_string.resize(bufferSize);
        
        _messages->receive(&serialized_string[0], bufferSize, recievedSize, priority);
        
        std::stringstream iss;
        iss << serialized_string;
        boost::archive::text_iarchive ia(iss);
        SharedMemoryData shMemBuffer;
        ia >> shMemBuffer;
        
        return shMemBuffer;
    }

private:
    std::string _shMemName;
    std::unique_ptr<boost::interprocess::message_queue> _messages;
};
