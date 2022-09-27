#include "CopyingTool.hpp"

#include <stdio.h>

#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <iostream>
#include <thread>

static constexpr size_t BUFFER_SIZE = 1024;

namespace ShMemCopyingTool
{
    CopyingTool::CopyingTool(
        std::string sourceFileName, std::string targetFileName, std::string shMemName)
        : _sourceFileName(std::move(sourceFileName)),
          _targetFileName(std::move(targetFileName)),
          _shMemName(std::move(shMemName))
    {
    }

    void CopyingTool::readFromFileAndWriteToShMem()
    {
        boost::interprocess::shared_memory_object::remove(_shMemName.c_str());

        using boost::interprocess::create_only;
        using boost::interprocess::read_write;

        constexpr boost::ulong_long_type   MAX_MESSAGES = 100;
        boost::interprocess::message_queue mq(
            create_only, _shMemName.c_str(), MAX_MESSAGES, BUFFER_SIZE);

        FileReader _fileReader;
        _fileReader.open(_sourceFileName);

        while (!_fileReader.isEndOfFile())
        {
            const auto bytesChunk = _fileReader.readNextBytesChunk(BUFFER_SIZE);
            SharedMemoryData shMemBuf{bytesChunk, _fileReader.isEndOfFile()};
            mq.send(&shMemBuf, sizeof(shMemBuf), 0);
        }
    }

    void CopyingTool::readFromShMemAndWriteToFile()
    {
        FileWriter _fileWriter;
        _fileWriter.open(_targetFileName);

        using boost::interprocess::open_only;
        using boost::interprocess::read_only;

        boost::interprocess::message_queue mq(open_only, _shMemName.c_str());
        boost::ulong_long_type             recievedSize;
        unsigned int                       priority;

        SharedMemoryData shMemBuffer;
        while (!shMemBuffer.isFinished())
        {
            mq.receive(&shMemBuffer, BUFFER_SIZE, recievedSize, priority);
            _fileWriter.writeBytesChunk(shMemBuffer.buffer);
            delete[] shMemBuffer.buffer;
            delete shMemBuffer.finish;
        }
        boost::interprocess::shared_memory_object::remove(_shMemName.c_str());
    }

}  // namespace ShMemCopyingTool
