#include <gtest/gtest.h>

#include <boost/filesystem.hpp>
#include <boost/process.hpp>
#include <iostream>

static auto currentFilePath = boost::filesystem::current_path() / "2_ReadWriteShMem.exe";

TEST(CopyingTool, ReaderAndWriterExecutionTime)
{
    try
    {
        boost::process::child reader(currentFilePath);
        boost::process::child writer(currentFilePath);
    
        reader.wait();
        writer.wait();
    }
    catch(boost::process::process_error& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

TEST(CopyingTool, ReadFromFileAndWriteToShMem)
{
    try
    {
        boost::process::child reader(currentFilePath);
        reader.wait();
    }
    catch (boost::process::process_error& e)
    {
        std::cerr << e.what() << std::endl;
    }
}
TEST(CopyingTool, ReadFromShMemAndWriteToFile)
{
    try
    {
        boost::process::child writer(currentFilePath);
        writer.wait();
    }
    catch (boost::process::process_error& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
