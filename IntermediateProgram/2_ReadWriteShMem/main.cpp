#include <iostream>
#include <string>

#include "CopyingTool.hpp"

int main()
{
    try
    {
        ShMemCopyingTool::CopyingTool ct("source.txt",
            "target.txt", "SharedMemory");

        ct.readFromFileAndWriteToShMem();
        ct.readFromShMemAndWriteToFile();
    }
    catch (const std::system_error& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}