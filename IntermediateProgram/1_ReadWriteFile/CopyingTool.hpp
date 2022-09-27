#pragma once

#include <atomic>
#include <string>

#include "FileReader.hpp"
#include "FileWriter.hpp"
#include "SafeQueue.hpp"

namespace FileCopyingTool
{
    class CopyingTool final
    {
    public:
        CopyingTool() = delete;
        CopyingTool(const std::string& sourceFileName, const std::string& targetFileName);
        CopyingTool(const CopyingTool&)            = delete;
        CopyingTool(CopyingTool&&)                 = delete;
        CopyingTool& operator=(const CopyingTool&) = delete;
        CopyingTool& operator=(CopyingTool&&)      = delete;

        ~CopyingTool() = default;

        void run();

    private:
        void reading();
        void copying();

    private:
        FileReader _fileReader;
        FileWriter _fileWriter;

        SafeQueue<std::vector<char>> _incomingData;
        std::atomic<bool>            _isFileRead = false;
    };

}  // namespace CopyingToolFile
