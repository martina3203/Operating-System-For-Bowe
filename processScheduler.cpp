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

Node<PCB> * processQueue::removeNode(Node<PCB> * targetPCB)
{
    return theList.removeNode(targetPCB);
}

void processQueue::printQueue()
{
    theList.printList();
    return;
}

void processQueue::printProcessInformation(std::string name)
{
    if (name != "ALL")
    {
        std::vector<PCB> currentList = theList.returnDataAsVector();
        for (unsigned int i = 0; i < currentList.size(); i++)
        {
            if (name == currentList.at(i).returnProcessName())
            {
                std::cout << "Name\t\t\t\tState\tProcess Type\tMemory Used\tPriority" << std::endl <<std::endl;
                std::cout << constructStringToSize(name,32);
                //Prints State of the Program
                if (currentList.at(i).returnCurrentState() == ready)
                {
                    std::cout << " Ready\t";
                }
                else
                {
                    std::cout << " Blocked\t";
                }

                //Prints type of program (System or Application)
                if (currentList.at(i).returnProcessType() == system)
                {
                    std::cout << "System\t\t";
                }
                else
                {
                    std::cout << "Application\t\t";
                }

                std::cout << currentList.at(i).returnAmountOfMemory() << "\t\t" << currentList.at(i).returnPriority() << std::endl;
                return;
            }
        }
        std::cout << "Process does not exist" << std::endl;
    }
    else
    {
        std::vector<PCB> currentList = theList.returnDataAsVector();
        if (currentList.size() != 0)
        {
            std::cout << "Name\t\t\t\tState\tProcess Type\tMemory Used\tPriority" << std::endl <<std::endl;
            for (unsigned int i = 0; i < currentList.size(); i++)
            {
                    std::cout << constructStringToSize(currentList.at(i).returnProcessName(),32);
                    //Prints State of the Program
                    if (currentList.at(i).returnCurrentState() == ready)
                    {
                        std::cout << "Ready\t";
                    }
                    else
                    {
                        std::cout << "Blocked\t";
                    }

                    //Prints type of program (System or Application)
                    if (currentList.at(i).returnProcessType() == system)
                    {
                        std::cout << "System\t\t";
                    }
                    else
                    {
                        std::cout << "Application\t\t";
                    }

                    std::cout << currentList.at(i).returnAmountOfMemory() << "\t\t" << currentList.at(i).returnPriority() << std::endl;
            }
        }
    }
    return;
}

void processQueue::test()
{
    PCB newPCB("Walnuts");
    PCB secondNewPCB("Chickens");
    PCB thirdNewPCB("Cucumbers");
    addProcess(secondNewPCB);
    addProcess(thirdNewPCB);
    addProcess(newPCB);
    printProcessInformation("ALL");
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

void processScheduler::test()
{
    PCB newPCB("Hi",1,system);

    Node<PCB> * newProcess = new Node<PCB>;
    setupPCB("Chicken Shit",1,system);
    setupPCB("Hot Pocket",1,system);
    newProcess = findPCB("Hot Pocket");
    removePCB(newProcess);
    std::cout << readyQueue.returnTotalNumberOfNodes();
    readyQueue.printQueue();

    return;
}



void processScheduler::setupPCB(std::string name,int priority,processType type)
{
    //Creates the new PCB
    if ((readyQueue.findProcess(name) == NULL) && (blockedQueue.findProcess(name) == NULL))
    {
        PCB newPCB(name,priority,type);
        std::cout << "Process Added" << std::endl;
        readyQueue.addProcess(newPCB);
    }
    else
    {
        std::cout << "Process Already Exists" << std::endl;
    }
    return;
}

void processScheduler::freePCB(Node<PCB> * targetPCB)
{
    delete targetPCB;
    targetPCB = NULL;
    return;
}


//Finds a particular PCB, if it exists
Node<PCB> * processScheduler::findPCB(std::string name)
{
    Node<PCB> * returnedNode = readyQueue.findProcess(name);
    //If it wasn't found in the ready queue, look in the blocked Queue
    if (returnedNode == NULL)
    {
        returnedNode = blockedQueue.findProcess(name);
    }

    //Return node; it will be NULL if it wasn't found
    return returnedNode;
}

//Inserts a process into the correct list
void processScheduler::insertPCB(Node<PCB> * newProcess)
{
    //Saved for easy reading
    PCB savedPCB = newProcess -> returnData();
    std::string nameOfProcess = savedPCB.returnProcessName();
    // If a Duplicate is found, print error and exit
    if (findPCB(nameOfProcess) != NULL)
    {
        std::cout << "Duplicate Found. Process was not inserted." << std::endl;
        return;
    }

    //If this is ready, add to ready Queue
    if (savedPCB.returnCurrentState() == ready)
    {
        readyQueue.addProcess(savedPCB);
        delete newProcess;
        newProcess = NULL;
    }
    //If this is blocked, add to blocked Queue
    else if (savedPCB.returnCurrentState() == blocked)
    {
        blockedQueue.addProcess(savedPCB);
        delete newProcess;
        newProcess = NULL;
    }
    //Else, I really messed up
    else
    {
        std::cout << "You done messed up in insertPCB" << std::endl;
    }
    return;
}

void processScheduler::removePCB(Node<PCB> * targetPCB)
{
    Node<PCB> * savedNode = findPCB(targetPCB -> returnData().returnProcessName());
    if(savedNode != NULL)
    {
        readyQueue.removeNode(savedNode);
        blockedQueue.removeNode(savedNode);
        //freePCB(targetPCB);
    }
    else
    {
        //Fail Message
        std::cout << "Process does not exist" << std::endl;
    }
    return;
}
