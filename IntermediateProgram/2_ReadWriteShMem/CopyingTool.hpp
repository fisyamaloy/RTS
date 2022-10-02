#pragma once

#include <atomic>
#include <string>

#include "FileReader.hpp"
#include "FileWriter.hpp"
#include "SafeQueue.hpp"

namespace ShMemCopyingTool
{
    struct SharedMemoryData
    {
        char* buffer;
        bool* finish;
        SharedMemoryData() : buffer(nullptr), finish(nullptr) {}
        SharedMemoryData(char* buffer, bool isFinish) : buffer(buffer), finish(new bool(isFinish))
        {
        }

        inline bool isFinished() const
        {
            if (finish) 
                return *finish;

            return false;
        }
    };

    class CopyingTool final
    {
    public:
        CopyingTool() = delete;
        CopyingTool(std::string sourceFileName, std::string targetFileName, std::string shMemName);
        CopyingTool(const CopyingTool&)            = delete;
        CopyingTool(CopyingTool&&)                 = delete;
        CopyingTool& operator=(const CopyingTool&) = delete;
        CopyingTool& operator=(CopyingTool&&)      = delete;

        ~CopyingTool() = default;

        bool isShMemNameFree() const;
        void readFromFileAndWriteToShMem();
        void readFromShMemAndWriteToFile();

    private:
        std::string _sourceFileName;
        std::string _targetFileName;
        std::string _shMemName;
    };

}  // namespace ShMemCopyingTool
