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
    //dtor
    /*
    for (int i = 0; i < SIZE_OF_MEMORY; i++)
    {
        if (memoryLocation[i] != NULL)
        {
            delete memoryLocation[i];
            memoryLocation[i] = NULL;
        }
    }
    */
}

void memoryManager::test()
{
    PCB testPCB("Poop");
    testPCB.setMemoryNeeded(100);
    insertFirstFit(testPCB);
    //printMemory();
    removeFromMemory("Poop");
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
    }
    return processAdded;
}

void memoryManager::removeFromMemory(std::string processName)
{
    for (int i = 0; i < SIZE_OF_MEMORY; i++)
    {
        if (memoryLocation[i] -> returnProcessName() == processName)
        {
            delete memoryLocation[i];
            memoryLocation[i] = NULL;
            return;
        }
    }
    return;
}
