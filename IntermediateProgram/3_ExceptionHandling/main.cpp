#include <iostream>
#include <string>

#include "CopyingTool.hpp"
#include "ShMemTerminationHandler.hpp"

static ExceptionHandlingTool::CopyingTool ct("source.txt", "target.txt", "shmem");

void termHandler() 
{
    ShMemTerminationHandler th;
    th.sendStateToSecondProcess(ShMemTerminationHandler::ERROR);

    while (th.getStateFromAnotherProcess() != ShMemTerminationHandler::SUCCESS)
    {
        // Eating processor's time to wait an answer from another process =(
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
    th.sendStateToSecondProcess(ShMemTerminationHandler::SUCCESS);
}
