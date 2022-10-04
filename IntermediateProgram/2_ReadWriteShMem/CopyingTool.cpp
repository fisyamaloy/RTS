#include "CopyingTool.hpp"

#include <stdio.h>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/serialization/string.hpp>
#include <iostream>
#include <string>
#include <thread>

static constexpr size_t BUFFER_SIZE = 1024;

struct SharedMemoryData
{
    std::string buffer;
    bool        finish;
    SharedMemoryData() : finish(false) {}
    SharedMemoryData(char* buffer, bool isFinish) : buffer(buffer), finish(isFinish) {}

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

namespace ShMemCopyingTool
{
    using boost::interprocess::create_only;
    using boost::interprocess::open_only;
    using boost::interprocess::read_only;
    using boost::interprocess::read_write;

    CopyingTool::CopyingTool(
        std::string sourceFileName, std::string targetFileName, std::string shMemName)
        : _sourceFileName(std::move(sourceFileName)),
          _targetFileName(std::move(targetFileName)),
          _shMemName(std::move(shMemName))
    {
    }

    bool CopyingTool::isShMemNameFree() const
    {
        try
        {
            boost::interprocess::shared_memory_object b{
                create_only, std::string(_shMemName + "dsff").c_str(), read_write};
            return true;
        }
        catch (boost::interprocess::interprocess_exception&)
        {
            boost::interprocess::shared_memory_object::remove(
                std::string(_shMemName + "dsff").c_str());
        }

        return false;
    }

    void CopyingTool::readFromFileAndWriteToShMem()
    {
        boost::interprocess::message_queue::remove(_shMemName.c_str());

        constexpr boost::ulong_long_type   MAX_MESSAGES = 100;
        boost::interprocess::message_queue mq(
            create_only, _shMemName.c_str(), MAX_MESSAGES, BUFFER_SIZE + sizeof(SharedMemoryData));

        FileReader _fileReader;
        _fileReader.open(_sourceFileName);

        while (!_fileReader.isEndOfFile())
        {
            const auto        bytesChunk = _fileReader.readNextBytesChunk(BUFFER_SIZE);
            SharedMemoryData  shMemBuf{bytesChunk, _fileReader.isEndOfFile()};
            
            std::stringstream oss;
            boost::archive::text_oarchive oa(oss);
            oa << shMemBuf;
            std::string serialized_string(oss.str());

            mq.send(serialized_string.data(), serialized_string.size(), 0);
        }
    }

    void CopyingTool::readFromShMemAndWriteToFile()
    {
        boost::interprocess::message_queue mq(open_only, _shMemName.c_str());
        boost::ulong_long_type             recievedSize;
        unsigned int                       priority;

        FileWriter _fileWriter;
        _fileWriter.open(_targetFileName);
        SharedMemoryData shMemBuffer;
        while (!shMemBuffer.isFinished())
        {
            std::stringstream iss;
            std::string       serialized_string;
            serialized_string.resize(BUFFER_SIZE + sizeof(SharedMemoryData));
            mq.receive(&serialized_string[0], BUFFER_SIZE + sizeof(SharedMemoryData), recievedSize,
                priority);
            iss << serialized_string;
            boost::archive::text_iarchive ia(iss);
            ia >> shMemBuffer;

            _fileWriter.writeBytesChunk(shMemBuffer.buffer.c_str());
        }

        boost::interprocess::message_queue::remove(_shMemName.c_str());
    }

}  // namespace ShMemCopyingTool
