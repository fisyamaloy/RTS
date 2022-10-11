#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "CopyingTool.hpp"

TEST(CopyingTool, readFromFileAndWriteToShMem)
{
    try
    {
        ShMemCopyingTool::CopyingTool ct("source.txt", "target.txt", "shmem");
        ct.readFromFileAndWriteToShMem();
    }
    catch (const std::system_error& e)
    {
        std::cerr << e.what() << '\n';
    }
}

TEST(CopyingTool, readFromShMemAndWriteToFile)
{
    try
    {
        ShMemCopyingTool::CopyingTool ct("source.txt", "target.txt", "shmem");
        ct.readFromShMemAndWriteToFile();
    }
    catch (const std::system_error& e)
    {
        std::cerr << e.what() << '\n';
    }
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
