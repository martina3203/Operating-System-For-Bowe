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
    if (theList.returnNodeCount() != 0)
    {
        if (name != "ALL")
        {
            std::vector<PCB> currentList = theList.returnDataAsVector();
            for (unsigned int i = 0; i < currentList.size(); i++)
            {
                if (name == currentList.at(i).returnProcessName())
                {
                    std::cout << "Name        | State |\tProc. Type | Memory Used | Priority | Time Remaining" << std::endl <<std::endl;
                    std::cout << constructStringToSize(name,14);
                    //Prints State of the Program
                    if (currentList.at(i).returnCurrentState() == ready)
                    {
                        std::cout << " Ready\t";
                    }
                    else if (currentList.at(i).returnCurrentState() == suspendReady)
                    {
                        std::cout << "Susp. Ready\t";
                    }
                    else if (currentList.at(i).returnCurrentState() == suspendBlocked)
                    {
                        std::cout << "Susp. Blocked\t";
                    }
                    else
                    {
                        std::cout << " Blocked\t";
                    }

                    //Prints type of program (System or Application)
                    if (currentList.at(i).returnProcessType() == system)
                    {
                        std::cout << "Sys.\t\t";
                    }
                    else
                    {
                        std::cout << "App.\t\t";
                    }

                    std::cout << currentList.at(i).returnAmountOfMemory() << "\t\t" << currentList.at(i).returnPriority() <<
                    "\t\t" << currentList.at(i).returnTimeRemaining() << std::endl;
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
                std::cout << "Name        | State |\tProc. Type | Memory Used | Priority | Time Remaining" << std::endl <<std::endl;
                for (unsigned int i = 0; i < currentList.size(); i++)
                {
                        if (i % 19 == 18)
                        {
                            pauseForUser();
                        }
                        std::cout << constructStringToSize(currentList.at(i).returnProcessName(),14);
                        //Prints State of the Program
                        if (currentList.at(i).returnCurrentState() == ready)
                        {
                            std::cout << "Ready\t";
                        }
                        else if (currentList.at(i).returnCurrentState() == suspendReady)
                        {
                            std::cout << "Susp. Ready\t";
                        }
                        else if (currentList.at(i).returnCurrentState() == suspendBlocked)
                        {
                            std::cout << "Susp. Blocked\t";
                        }
                        else
                        {
                            std::cout << "Blocked\t";
                        }

                        //Prints type of program (System or Application)
                        if (currentList.at(i).returnProcessType() == system)
                        {
                            std::cout << "  Sys.\t\t";
                        }
                        else
                        {
                            std::cout << "  App.\t\t";
                        }

                        std::cout << currentList.at(i).returnAmountOfMemory() << "\t\t" << currentList.at(i).returnPriority() <<
                            "\t\t" << currentList.at(i).returnTimeRemaining() << std::endl;
                }
            }
        }

        return;
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
    ShortestJobFirst();

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
    if (savedPCB.returnCurrentState() == ready || savedPCB.returnCurrentState() == suspendReady)
    {
        readyQueue.addProcess(savedPCB);
        delete newProcess;
        newProcess = NULL;
    }
    //If this is blocked, add to blocked Queue
    else if (savedPCB.returnCurrentState() == blocked || savedPCB.returnCurrentState() == suspendBlocked)
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
    if (savedNode != NULL)
    {
        if (readyQueue.removeNode(savedNode) != NULL)
        {
            //std::cout << "Process removed from Ready Queue" << std::endl;
        }
        else if (blockedQueue.removeNode(savedNode) != NULL)
        {
            //std::cout << "Process removed from Blocked Queue" << std::endl;
        }
        //freePCB(targetPCB);
    }
    else
    {
        //Fail Message
        std::cout << "Process does not exist" << std::endl;
    }
    return;
}

void processScheduler::commandHandler(command newCommand)
{
    newCommand.convert(2);
    std::string secondaryInformation = newCommand.returnTargetInformation();

    if (secondaryInformation == "createprocess")
    {
        //Creation of Process
        int userNumber;
        int processPriorityNumber;
        bool validAnswer = false;
        std::cout << "Input Process Name: " << std::endl;
        std::string process;
        std::cin >> process;

        //Checks and receives a valid priority number
        while (validAnswer == false)
        {
            std::cout << "Input the priority number: " << std::endl;
            std::cin >> userNumber;
            if ((userNumber < 128) && (userNumber > -127))
            {
                validAnswer = true;
                processPriorityNumber = userNumber;
            }
            else
            {
                std::cout << "Invalid priority number:" << std::endl;
            }
        }
        validAnswer = false;
        //Checks and receives system or application
        while (validAnswer == false)
        {
            int userNumber;
            std::cout << "Press 1 for system or 2 for application" << std::endl;
            std::cin >> userNumber;
            if (userNumber == 1)
            {
                setupPCB(process,processPriorityNumber,system);
                validAnswer = true;
            }
            else if (userNumber == 2)
            {
                setupPCB(process,processPriorityNumber,application);
                validAnswer = true;
            }
            else
            {
                std::cout << "Invalid Answer" << std::endl;
            }
        }
    }
    else if (secondaryInformation == "SJF")
    {
        //Execute ProcessScheduler
        ShortestJobFirst();
    }
    else if (secondaryInformation == "deleteprocess")
    {
        //Delete Process Command Handling
        std::string targetProcess;
        std::cout << "List name of the process to be deleted: " << std::endl;
        std::cin >> targetProcess;
        removePCB(findPCB(targetProcess));
    }

    else if (secondaryInformation == "blockprocess")
    {
        std::string targetProcess;
        std::cout << "List name of the process to be blocked: " << std::endl;
        std::cin >> targetProcess;
        Node<PCB> * savedNode = findPCB(targetProcess);
        if (savedNode != NULL)
        {
            PCB savedPCB = savedNode -> returnData();
            savedPCB.setCurrentState(blocked);
            removePCB(savedNode);
            savedNode -> setData(savedPCB);
            insertPCB(savedNode);
        }
        else
        {
            std::cout << "Process Not Found" << std::endl;
        }
    }

    else if (secondaryInformation == "unblockprocess")
    {
        std::string targetProcess;
        std::cout << "List name of the process to be set to ready: " << std::endl;
        std::cin >> targetProcess;
        Node<PCB> * savedNode = findPCB(targetProcess);
        if (savedNode != NULL)
        {
            PCB savedPCB = savedNode -> returnData();
            savedPCB.setCurrentState(ready);
            removePCB(savedNode);
            savedNode -> setData(savedPCB);
            insertPCB(savedNode);
        }
        else
        {
            std::cout << "Process Not Found" << std::endl;
        }
    }

    else if (secondaryInformation == "suspendprocess")
    {
        std::string targetProcess;
        std::cout << "List name of the process to be set to ready: " << std::endl;
        std::cin >> targetProcess;
        Node<PCB> * savedNode = findPCB(targetProcess);
        if (savedNode != NULL)
        {
            PCB savedPCB = savedNode -> returnData();
            if (savedPCB.returnCurrentState() == suspendBlocked || savedPCB.returnCurrentState() == blocked)
            {
                savedPCB.setCurrentState(suspendBlocked);
            }
            else
            {
                savedPCB.setCurrentState(suspendReady);
            }
            removePCB(savedNode);
            savedNode -> setData(savedPCB);
            insertPCB(savedNode);
        }
        else
        {
            std::cout << "Process Not Found" << std::endl;
        }
    }
    else if (secondaryInformation == "resumeprocess")
    {
        std::string targetProcess;
        std::cout << "List name of the process to be set to ready: " << std::endl;
        std::cin >> targetProcess;
        Node<PCB> * savedNode = findPCB(targetProcess);
        if (savedNode != NULL)
        {
            PCB savedPCB = savedNode -> returnData();
            if (savedPCB.returnCurrentState() == suspendBlocked || savedPCB.returnCurrentState() == blocked)
            {
                savedPCB.setCurrentState(blocked);
            }
            else
            {
                savedPCB.setCurrentState(ready);
            }
            removePCB(savedNode);
            savedNode -> setData(savedPCB);
            insertPCB(savedNode);
        }
        else
        {
            std::cout << "Process Not Found" << std::endl;
        }
    }

    else if (secondaryInformation == "setpriority")
    {
        std::string targetProcess;
        std::cout << "List name of the process you wish to change: " << std::endl;
        std::cin >> targetProcess;
        int newPriority = 10000;
        Node<PCB> * currentNode = findPCB(targetProcess);
        PCB newPCB = currentNode -> returnData();
        if (currentNode == NULL)
        {
            std::cout << "Process does not exist" << std::endl;
            return;
        }
        while (newPriority > 128 || newPriority < -127 )
        {
            std::cout << "Please state the new priority level as an integer range -127 to 128:" << std::endl;
            std::cin >> newPriority;
        }
        newPCB.setPriority(newPriority);
        currentNode -> setData(newPCB);
    }
    else if (secondaryInformation == "printready")
    {
        readyQueue.printProcessInformation("ALL");
    }
    else if (secondaryInformation == "printblocked")
    {
        blockedQueue.printProcessInformation("ALL");
    }
    else if (secondaryInformation == "printprocess")
    {
        std::string targetProcess;
        std::cout << "List name of the process to be printed: " << std::endl;
        std::cin >> targetProcess;
        readyQueue.printProcessInformation(targetProcess);
        blockedQueue.printProcessInformation(targetProcess);
    }
    else if (secondaryInformation == "printall")
    {
        readyQueue.printProcessInformation("ALL");
        blockedQueue.printProcessInformation("ALL");
    }
    else
    {
        std::cout << "Unknown Command" << std::endl;
    }
    std::cin.ignore();
}

std::vector<PCB> processScheduler::readProcessesFromFile(std::string fileName)
{
    std::fstream openedFile;
    openedFile.open(fileName.c_str());
    //Variables for saving
    std::string processName;
    std::vector<PCB> returnedVector;
    char typeOfProcess;
    processType newType;
    int priorityOfNewProcess;
    int memoryNeeded;
    int timeRemaining;
    int arrivalTime;
    int CPUPercentage;

    //If the file is opened
    if (openedFile.is_open())
    {
        std::cout << "File opened" << std::endl;
        //While reading a file
        while (!openedFile.eof())
        {
            //Read Process Name
            openedFile >> processName;

            //Read process type A or S
            openedFile >> typeOfProcess;
            if (typeOfProcess != 'A' && typeOfProcess != 'S')
            {
                std::cout << "Invalid format. Reading Terminated." << std::endl;
                break;
            }
            if (typeOfProcess == 'A')
            {
                newType = application;
            }
            else
            {
                newType = system;
            }
            //Read Priority Number
            openedFile >> priorityOfNewProcess;
            if (priorityOfNewProcess > 128 && priorityOfNewProcess < -127)
            {
                std::cout << "Invalid format. Reading Terminated." << std::endl;
                break;
            }
            //Read Memory
            openedFile >> memoryNeeded;
            //Read time remaining in process
            openedFile >> timeRemaining;
            //Arrival time
            openedFile >> arrivalTime;
            //Read CPU Percentage
            openedFile >> CPUPercentage;

            std::cout << "Process " << processName << " loaded." << std::endl;

            //Create Process
            PCB newPCB(processName,priorityOfNewProcess,newType);
            newPCB.setMemoryNeeded(memoryNeeded);
            newPCB.setTimeRemaining(timeRemaining);
            newPCB.setArrivalTime(arrivalTime);
            newPCB.setCPUPercentage(CPUPercentage);

            //Add to returned Vector
            returnedVector.push_back(newPCB);
        }

    }
    //Can't find file
    else
    {
        std::cout << "File does not exist" << std::endl;
    }

    openedFile.close();
    return returnedVector;
}


void processScheduler::ShortestJobFirst()
{
    std::string fileName;
    std::vector<PCB> PCBvector;
    Node<PCB> * currentPCB;

    //Ask for file name
    std::cout << "Please input a file name: " << std::endl;
    std::cin >> fileName;
    PCBvector = readProcessesFromFile(fileName);

    //Sort vector based on time til completion.
    sortVectorByTimeRemaining(PCBvector);

    for (unsigned int i = 0; i < PCBvector.size(); i++)
    {
        currentPCB = new Node<PCB>;
        currentPCB -> setData(PCBvector.at(i));
        insertPCB(currentPCB);

    }
    //Print list with completion time showing.
    readyQueue.printProcessInformation("ALL");
    //"Execute" list and return the time until completion

    int currentTime = 0;
    int totalTime = 0;
    int averageTurnAroundTime = 0;
    runningProcess = NULL;
    //While list is not empty and there is no active nodes
    while ((readyQueue.returnTotalNumberOfNodes() != 0) || (runningProcess != NULL))
    {
        if (runningProcess == NULL)
        {
            //Make first program the running process
            runningProcess = readyQueue.returnHeadProcess();
            //Find and remove this process from the Ready queue
            std::cout << runningProcess -> returnData().returnProcessName() << " is now running." << std::endl;
            currentTime = runningProcess -> returnData().returnTimeRemaining();
            totalTime = totalTime + currentTime;
            averageTurnAroundTime = averageTurnAroundTime + totalTime;
            std::cout << averageTurnAroundTime;
            removePCB(runningProcess);
        }
        currentTime = currentTime--;
        if (currentTime <= 0)
        {
            //Remove PCB as the job is completed
            std::cout << runningProcess -> returnData().returnProcessName() << " has finished running." << std::endl;
            freePCB(runningProcess);
            runningProcess = NULL;
        }
    }
    //calculate turnaround time
    averageTurnAroundTime = averageTurnAroundTime / PCBvector.size();


    std::cout << "Process Queue was completed in " << totalTime << " Seconds." << std::endl;
    std::cout << "The average turnaround time is " << averageTurnAroundTime << " Seconds." << std::endl;
}
