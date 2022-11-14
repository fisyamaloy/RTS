#include <iostream>
#include <string>
#include <exception>
#include <cstdlib>

#include "FileReader.hpp"
#include "FileWriter.hpp"
#include "CopyingTool.hpp"
#include "TerminationManipulator.hpp"
#include <chrono>
#include "ShMemReader.hpp"

static ExceptionHandlingTool::CopyingTool ct("source.txt", "target.txt", "shddmem");

static TerminationManipulator tm;

void termHandler() 
{
    tm.setTerminationState(TerminationManipulator::ERROR);
    
    int SECONDS_TO_WAIT = 15; // need if exceptions are thrown by both processes 
    while (tm.getTerminationState() != TerminationManipulator::SUCCESS)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (SECONDS_TO_WAIT == 0)
            break;
        SECONDS_TO_WAIT--;
    }

    ct.cleanActiveShMems();
    std::cout << "Own terminate function called" << std::endl;
    std::abort();
}

int main()
{
    std::set_terminate(termHandler);
    bool isWriterToShMem = ct.isShMemNameFree();

    if (isWriterToShMem)
        ct.copyFileDataToShMem();
    else
        ct.copyShMemDataToFile();

    tm.setTerminationState(TerminationManipulator::SUCCESS);

    return 0;
}
