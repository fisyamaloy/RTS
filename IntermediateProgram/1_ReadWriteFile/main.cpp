#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "CopyingTool.hpp"

TEST(CopyingTool, run)
{
    try
    {
        FileCopyingTool::CopyingTool ct("source.txt", "target.txt");
        ct.run();
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