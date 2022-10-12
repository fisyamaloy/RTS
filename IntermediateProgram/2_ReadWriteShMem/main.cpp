#include <iostream>
#include <string>

#include "CopyingTool.hpp"

#include <boost/process.hpp>

int main()
{
    try
    {
        ShMemCopyingTool::CopyingTool ct("source.txt", "target.txt", "shmem");
        if (ct.isShMemNameFree())
            ct.readFromFileAndWriteToShMem();
        else
            ct.readFromShMemAndWriteToFile();
    }
    catch (const std::system_error& e)
    {
        std::cerr << e.what() << '\n';
    }
}
