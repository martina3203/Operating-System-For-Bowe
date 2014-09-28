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
        void setTimeRemaining(int);
        void setArrivalTime(int);
        void setCPUPercentage(int);

        //Return Functions
        std::string returnProcessName();
        processType returnProcessType();
        processState returnCurrentState();
        int returnPriority();
        int returnAmountOfMemory();
        int returnTimeRemaining();
        int returnArrivalTime();
        int returnCPUPercentage();
        int returnTickets();

    protected:
    private:
        std::string processName;
        processType TypeOfProcess;
        processState currentState;
        int priority;
        int memoryAllocatedAmount;
        int timeRemaining;
        int arrivalTime;
        int CPUPercentageInUse;
        int tickets;

};

#endif // PCB_H
