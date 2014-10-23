#include "PCB.h"

PCB::PCB()
{
    //Constructor
    timeRemaining = 1;
}

PCB::PCB(std::string newName,int priority, processType type)
{
    //Sets attributes based on parameters
    processName = newName;
    this -> priority = priority;
    TypeOfProcess = type;
    currentState = ready;
    memoryAllocatedAmount = 1;
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
void PCB::setCurrentState(processState newState)
{
    currentState = newState;
    return;
}

void PCB::setPriority(int newPriority)
{
    priority = newPriority;
}

void PCB::setArrivalTime(int newTime)
{
    arrivalTime = newTime;
}

void PCB::setTimeRemaining(int newTime)
{
    timeRemaining = newTime;
}

void PCB::setCPUPercentage(int newPercentage)
{
    CPUPercentageInUse = newPercentage;
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

int PCB::returnArrivalTime()
{
    return arrivalTime;
}

int PCB::returnCPUPercentage()
{
    return CPUPercentageInUse;
}

int PCB::returnTimeRemaining()
{
    return timeRemaining;
}
