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


class PCB
{
    public:
        PCB();
        PCB(std::string newName,processType type = system);
        virtual ~PCB();
        void testPCB();

        //Return Functions
        std::string returnProcessName();
        processType returnProcessType();
        int returnPriority();
        int returnAmountOfMemory();

    protected:
    private:
        std::string processName;
        processType TypeOfProcess;
        int priority;
        int memoryAllocatedAmount;

};

#endif // PCB_H
