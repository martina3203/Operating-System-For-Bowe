#include "PCB.h"

PCB::PCB()
{
    //Constructor
}

PCB::PCB(std::string newName, processType type)
{
    processName = newName;
    TypeOfProcess = type;
}

PCB::~PCB()
{
    //Destructor
}

void PCB::testPCB()
{
    std::cout << "Process Name: " << returnProcessName() << std::endl;
    std::cout << "Process Type(0 for system, 1 for application): " << returnProcessType() << std::endl;
}

//Return Functions
std::string PCB::returnProcessName()
{
    return processName;
}

//Returns the type of Process
processType PCB::returnProcessType()
{
    return TypeOfProcess;
}

//Returns the numerical priority of the process
int PCB::returnPriority()
{
    return priority;
}

//Returns the amount of memory the process takes up
int PCB::returnAmountOfMemory()
{
    return memoryAllocatedAmount;
}
