#ifndef PCB_H
#define PCB_H

#include <string>
#include <iostream>

#define system System


enum processType
{
    system,
    application
};

enum processState
{
    running,
    ready,
    blocked
};


class PCB
{
    public:
        PCB();
        PCB(std::string newName,int priority = 1,processType type = system);
        virtual ~PCB();
        void testPCB();

        //Setters
        void setMemoryNeeded(int);
        void setCurrenState(processState);

        //Return Functions
        std::string returnProcessName();
        processType returnProcessType();
        processState returnCurrentState();
        int returnPriority();
        int returnAmountOfMemory();

    protected:
    private:
        std::string processName;
        processType TypeOfProcess;
        processState currentState;
        int priority;
        int memoryAllocatedAmount;

};

#endif // PCB_H
