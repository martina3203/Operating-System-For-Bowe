#ifndef PROCESSSCHEDULER_H
#define PROCESSSCHEDULER_H

#include <stdlib.h>
#include <time.h>

#include "linkedList.h"
#include "personalFunctions.h"
#include "command.h"
#include <string>
#include <fstream>


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
    std::vector<PCB> returnVector();
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
        std::vector<PCB> readProcessesFromFile(std::string fileName);
    protected:
    private:
        void ShortestJobFirst(functionPointer);
        void FirstInFirstOut(functionPointer);
        void STCF(functionPointer);
        void FPPS(functionPointer);
        void roundRobin(functionPointer);
        void lottery(functionPointer);
        void MLQF();
        Node<PCB> * runningProcess;
        //Substructures
        processQueue readyQueue;
        processQueue blockedQueue;
        memoryManager OSMemory;
};

#endif // PROCESSSCHEDULER_H
