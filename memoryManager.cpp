#include "memoryManager.h"

memoryManager::memoryManager()
{
    //Set all positions to NULL before starting
    for (int i = 0; i < SIZE_OF_MEMORY;i++)
    {
        memoryLocation[i] = NULL;
    }
    //Default Address
    savedAddress = 0;
}

memoryManager::~memoryManager()
{
    //Destructor
}

void memoryManager::test()
{
    PCB testPCB("Poop");
    PCB AnotherPCB("Hey");
    testPCB.setMemoryNeeded(100);
    AnotherPCB.setMemoryNeeded(200);
    insertFirstFit(testPCB);
    insertFirstFit(AnotherPCB);
    printMemory();
    removeFromMemory("Poop");
    removeFromMemory("Hey");
    printMemory();
    return;
}

void memoryManager::printMemory()
{
    for (int i = 0; i < SIZE_OF_MEMORY; i++)
    {
        if (memoryLocation[i] != NULL)
        {
            std::cout << i+1 << ". " << memoryLocation[i] -> returnProcessName() << std::endl;
        }
    }
    return;
}

bool memoryManager::insertFirstFit(PCB runningProcess)
{
    bool processAdded = false;
    //Grab amount of memory needed by the process
    int memoryNeeded = runningProcess.returnAmountOfMemory();
    //Traverse to find a suitable location for process
    for (int i = 0; i < SIZE_OF_MEMORY; i++)
    {
        //If we have arrived at an empty spot
        if (memoryLocation[i] == NULL)
        {
            int segmentCounter = 0;
            int currentPosition = i;
            //Check if the segment is big enough for this process
            for (int j = currentPosition; currentPosition < SIZE_OF_MEMORY; j++)
            {
                //If this spot is still empty
                if (memoryLocation[j] == NULL)
                {
                    //Add to counter
                    segmentCounter++;
                    if (segmentCounter == memoryNeeded)
                    {
                        //Add Process at the starting location
                        PCB * processPointer = new PCB;
                        processPointer = &runningProcess;
                        memoryLocation[currentPosition] = processPointer;
                        processAdded = true;
                        return processAdded;
                    }
                }
                else
                {
                    processAdded = false;
                    break;
                }
            }
        }
        else
        {
            //Jump to next available position after memory segment
            i = i + memoryLocation[i] -> returnAmountOfMemory()-1;
        }
    }
    return processAdded;
}

void memoryManager::removeFromMemory(std::string processName)
{
    for (int i = 0; i < SIZE_OF_MEMORY; i++)
    {
        //If a process is found
        if (memoryLocation[i] != NULL)
        {
            //If the process has the same name as the parameter
            if ((memoryLocation[i] -> returnProcessName()) == processName)
            {
                //Delete it
                delete memoryLocation[i];
                memoryLocation[i] = NULL;
                std::cout << "Delete Completed" << std::endl;
                return;
            }
        }
    }

    //This only happens if the node is not found
    std::cout << "Process not found in memory" << std::endl;
}
