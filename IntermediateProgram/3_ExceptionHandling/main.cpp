#include <iostream>
#include <string>

#include "CopyingTool.hpp"
#include "ShMemTerminationHandler.hpp"
#include <chrono>

static ExceptionHandlingTool::CopyingTool ct("source.txt", "target.txt", "shmem");

void termHandler() 
{
    ShMemTerminationHandler th;
    th.sendStateToAnotherProcess(ShMemTerminationHandler::ERROR);
    
    int SECONDS_TO_WAIT = 15; // need if exceptions are thrown by both processes 
    while (th.getStateFromAnotherProcess() != ShMemTerminationHandler::SUCCESS)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (SECONDS_TO_WAIT == 0)
            break;
        SECONDS_TO_WAIT--;
    }

    ct.cleanActiveShMems();
    std::cout << "Own terminate function called" << std::endl;
}

int main()
{
    set_terminate(termHandler);
    
    if (ct.isWriterToShMem())
        ct.readFromFileAndWriteToShMem();
    else
        ct.readFromShMemAndWriteToFile();

    ShMemTerminationHandler th;
    th.sendStateToAnotherProcess(ShMemTerminationHandler::SUCCESS);
}
