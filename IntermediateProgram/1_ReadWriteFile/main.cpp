#include <iostream>
#include <string>
#include "CopyingTool.hpp"
#include <gtest/gtest.h>

TEST(CopyingTool, run)
{
    try
    {
        CopyingTool ct("C:\\Users\\Danil_Fisiuk\\Desktop\\source.txt",
                       "C:\\Users\\Danil_Fisiuk\\Desktop\\target.txt");
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