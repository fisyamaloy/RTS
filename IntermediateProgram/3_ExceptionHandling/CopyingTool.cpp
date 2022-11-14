#include "CopyingTool.hpp"

#include <stdio.h>

#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <iostream>
#include <string>

#include "FileReader.hpp"
#include "FileWriter.hpp"
#include "ShMemReader.hpp"
#include "ShMemWriter.hpp"
#include "SharedMemoryData.hpp"

static constexpr size_t                 BUFFER_SIZE  = 4096;
static constexpr boost::ulong_long_type MAX_MESSAGES = 100000;

namespace ExceptionHandlingTool
{
    using boost::interprocess::create_only;
    using boost::interprocess::read_write;

    CopyingTool::CopyingTool(
        std::string sourceFileName, std::string targetFileName, std::string shMemName)
        : _sourceFileName(std::move(sourceFileName)),
          _targetFileName(std::move(targetFileName)),
          _shMemName(std::move(shMemName))
    {
    }

    std::string CopyingTool::strToCheckSmMemOnFree() const
    {
        return _shMemName + "isFree";
    }

    bool CopyingTool::isShMemNameFree() const noexcept
    {
        const auto str = strToCheckSmMemOnFree();
        try
        {
            boost::interprocess::shared_memory_object b{create_only, str.c_str(), read_write};
            return true;
        }
        catch (boost::interprocess::interprocess_exception&)
        {
            boost::interprocess::shared_memory_object::remove(str.c_str());
        }

        return false;
    }

    void CopyingTool::cleanActiveShMems()
    {
        const auto str = strToCheckSmMemOnFree();
        boost::interprocess::shared_memory_object::remove(str.c_str());
        boost::interprocess::message_queue::remove(_shMemName.c_str());
    }

    void CopyingTool::copyFileDataToShMem()
    {
        boost::interprocess::message_queue::remove(_shMemName.c_str());

        FileReader _fileReader;
        _fileReader.open(_sourceFileName);

        ShMemWriter shMemWriter(_shMemName, MAX_MESSAGES, BUFFER_SIZE + sizeof(SharedMemoryData));
        while (!_fileReader.isEndOfFile())
        {
            const auto       bytesChunk = _fileReader.readNextBytesChunk(BUFFER_SIZE);
            SharedMemoryData shMemBuf{bytesChunk, _fileReader.isEndOfFile()};
            shMemWriter.write(shMemBuf);
        }
    }

    void CopyingTool::copyShMemDataToFile()
    {
        FileWriter _fileWriter;
        _fileWriter.open(_targetFileName);

        ShMemReader      shMemReader(_shMemName);
        SharedMemoryData shMemBuffer;
        while (!shMemBuffer.isFinished())
        {
            shMemBuffer = shMemReader.read(BUFFER_SIZE + sizeof(SharedMemoryData));
            _fileWriter.writeBytesChunk(shMemBuffer.buffer.c_str());
        }
    }

}  // namespace ExceptionHandlingTool
