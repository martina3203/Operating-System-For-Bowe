#ifndef PROCESSSCHEDULER_H
#define PROCESSSCHEDULER_H

#include "linkedList.h"
#include "personalFunctions.h"
#include "command.h"
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
    Node<PCB> * removeNode(Node<PCB> * targetPCB);
    int returnTotalNumberOfNodes();
    void printQueue();
    void printProcessInformation(std::string name);
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
        void test();
        void setupPCB(std::string name,int priority, processType type);
        Node<PCB> * findPCB(std::string name);
        void insertPCB(Node<PCB> * newProcess);
        void removePCB(Node<PCB> * targetPCB);
        void freePCB(Node<PCB> * targetPCB);
        void commandHandler(command newCommand);
    protected:
    private:
        PCB currentProcess;
        processQueue readyQueue;
        processQueue blockedQueue;
};

#endif // PROCESSSCHEDULER_H
