#include "processScheduler.h"

processQueue::processQueue()
{
    //Constructor
}

processQueue::~processQueue()
{
    //Destructor
}

//Simply adds to the list at the front
void processQueue::addProcess(PCB newProcess)
{
    theList.addToFront(newProcess);
    return;
}

//Returns the process as the PCB itself
PCB processQueue::removeProcess()
{
    return theList.removeFromBack();
}

//Returns the first process as a pointer
Node<PCB> * processQueue::returnHeadProcess()
{
    return theList.returnHeadNode();
}

//Returns the last process as a pointer
Node<PCB> * processQueue::returnLastProcess()
{
    return theList.returnLastNode();
}

Node<PCB> * processQueue::findProcess(std::string name)
{
    return theList.findNode(name);
}

//Returns an int representing the number of nodes
int processQueue::returnTotalNumberOfNodes()
{
    return theList.returnNodeCount();
}

void processQueue::test()
{
    PCB newPCB("Walnuts");
    PCB secondNewPCB("Chickens");
    PCB thirdNewPCB("Cucumbers");
    addProcess(secondNewPCB);
    addProcess(thirdNewPCB);
    addProcess(newPCB);
    removeProcess();
    theList.printList();
    std::cout << returnTotalNumberOfNodes();
    return;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
//Scheduler Functions
//////////////////////////////////////////////////////////////////////////////////////////////////////


processScheduler::processScheduler()
{
    //Constructor
}

processScheduler::~processScheduler()
{
    //Destructor
}

void processScheduler::setupPCB(std::string name,int priority,processType type)
{
    //Creates the new PCB
    if ((readyQueue.findProcess(name) == NULL) && (blockedQueue.findProcess(name) == NULL))
    {
        PCB newPCB(name,priority,type);
        readyQueue.addProcess(newPCB);
    }
    else
    {
        std::cout << "Process Already Exists" << std::endl;
    }

}

