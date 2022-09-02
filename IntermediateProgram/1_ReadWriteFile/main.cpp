#include <iostream>
#include "CopyingTool.hpp"
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

int main()
{
    try
    {
        CopyingTool ct("C:\\Users\\Danil_Fisiuk\\Desktop\\source.txt",
                       "C:\\Users\\Danil_Fisiuk\\Desktop\\target.txt");
        ct.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
