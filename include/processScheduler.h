#ifndef PROCESSSCHEDULER_H
#define PROCESSSCHEDULER_H

#include "linkedList.h"
#include <string>


class processQueue
{
public:
    processQueue();
    ~processQueue();

    void addProcess(PCB newProcess);
    PCB removeProcess();

    //Returns Values and data within
    Node<PCB> * returnHeadProcess();
    Node<PCB> * returnLastProcess();
    Node<PCB> * findProcess(std::string name);
    int returnTotalNumberOfNodes();
    void test();
private:
    linkedList theList;
    int totalNumberOfNodes;

};






class processScheduler
{
    public:
        processScheduler();
        virtual ~processScheduler();
        void setupPCB(std::string name,int priority, processType type);
    protected:
    private:
        PCB currentProcess;
        processQueue readyQueue;
        processQueue blockedQueue;
};

#endif // PROCESSSCHEDULER_H
