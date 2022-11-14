#pragma once

#include <atomic>
#include <string>

#include "SafeQueue.hpp"

namespace ExceptionHandlingTool
{
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

        bool isShMemNameFree() const noexcept;
        void cleanActiveShMems();
        void copyFileDataToShMem();
        void copyShMemDataToFile();
        
    private:
        std::string strToCheckSmMemOnFree() const;

    private:
        std::string _sourceFileName;
        std::string _targetFileName;
        std::string _shMemName;
    };

}  // namespace ShMemCopyingTool
