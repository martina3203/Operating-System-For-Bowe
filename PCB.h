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
    ready,
    suspendReady,
    suspendBlocked,
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
        void setCurrentState(processState);
        void setPriority(int);

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
