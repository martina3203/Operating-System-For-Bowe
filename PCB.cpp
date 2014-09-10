#include "PCB.h"

PCB::PCB()
{
    //Constructor
}

PCB::PCB(std::string newName,int priority, processType type)
{
    //Sets attributes based on parameters
    processName = newName;
    this -> priority = priority;
    TypeOfProcess = type;
    currentState = ready;
}

PCB::~PCB()
{
    //Destructor
}

void PCB::testPCB()
{
    std::cout << "Process Name: " << returnProcessName() << std::endl;
    std::cout << "Process Type(0 for system, 1 for application): " << returnProcessType() << std::endl;
    std::cout << "Memory Allocated: " << memoryAllocatedAmount << std::endl;
    std::cout << "Current State: " << currentState << std::endl;
}


//Setters Functions
//Changes memory allocated
void PCB::setMemoryNeeded(int newNumber)
{
    memoryAllocatedAmount = newNumber;
    return;
}

//Changes the state of the process
void PCB::setCurrenState(processState newState)
{
    currentState = newState;
    return;
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

processState PCB::returnCurrentState()
{
    return currentState;
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
