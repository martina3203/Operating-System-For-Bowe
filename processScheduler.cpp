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

std::vector<PCB> processQueue::returnVector()
{
    return theList.returnDataAsVector();
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
    //Converts all information to a lower case setting
    std::string secondaryInformation = newCommand.returnTargetInformation();

    //First In First Out
    if (secondaryInformation == "fifo")
    {
        FirstInFirstOut(returnMemoryInsertionMethod());
    }
    //Shortest Job First
    else if (secondaryInformation == "sjf")
    {
        //Execute ProcessScheduler
        ShortestJobFirst(returnMemoryInsertionMethod());
    }
    //Shortest time to Completion First
    else if (secondaryInformation == "stcf")
    {
        STCF(returnMemoryInsertionMethod());
    }
    //First Priority Pre-Emptive Scheduling
    else if (secondaryInformation == "fpps")
    {
        FPPS(returnMemoryInsertionMethod());
    }
    //Round Robin
    else if (secondaryInformation == "roundrobin")
    {
        roundRobin(returnMemoryInsertionMethod());
    }
    //Lottery Schedule
    else if (secondaryInformation == "lottery")
    {
        lottery(returnMemoryInsertionMethod());
    }
    //Suspend a process named by the user
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

void processScheduler::ShortestJobFirst(functionPointer InsertionMethod)
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
            if ((OSMemory.*InsertionMethod)(runningProcess -> returnData()) == false)
            {
                std::cout << "Process is too big to run on this system." << std::endl;
                return;
            }
            std::cout << runningProcess -> returnData().returnProcessName() << " is now running." << std::endl;
            currentTime = runningProcess -> returnData().returnTimeRemaining();
            totalTime = totalTime + currentTime;
            averageTurnAroundTime = averageTurnAroundTime + totalTime;
            removePCB(runningProcess);
        }

        currentTime = currentTime--;
        if (currentTime <= 0)
        {
            //Remove PCB as the job is completed
            std::cout << runningProcess -> returnData().returnProcessName() << " has finished running." << std::endl;
            std::cout << "Current Time: " << currentTime << std::endl;
            OSMemory.removeFromMemory(runningProcess -> returnData().returnProcessName());
            freePCB(runningProcess);
            runningProcess = NULL;
        }
    }
    //calculate turnaround time
    averageTurnAroundTime = averageTurnAroundTime / PCBvector.size();

    //Output useful information
    std::cout << "Process Queue was completed in " << totalTime << " Seconds." << std::endl;
    std::cout << "The average turnaround time is " << averageTurnAroundTime << " Seconds." << std::endl;
    OSMemory.resetMemory();
    return;
}

void processScheduler::FirstInFirstOut(functionPointer InsertionMethod)
{
    std::string fileName;
    std::vector<PCB> PCBvector;
    Node<PCB> * currentPCB;
    std::ofstream outputFile;
    outputFile.open("FIFO.txt");

    //Ask for file name
    std::cout << "Please input a file name: " << std::endl;
    std::cin >> fileName;
    PCBvector = readProcessesFromFile(fileName);

    //Sort vector based on arrivalTime
    sortVectorByArrivalTime(PCBvector);

    int currentTime = 0;
    int processRunTime = 0;
    int averageTurnAroundTime = 0;
    int totalProcesses = PCBvector.size();
    runningProcess = NULL;

    //While there is possible jobs
    while (PCBvector.size() != 0 || runningProcess != NULL)
    {
        //Travel through the vector and find any programs that must be added to the queue
        for (int i = PCBvector.size()-1; i >= 0; i--)
        {
            //If the process's arrival time is appropriate, add it to the queue and remove from the vector
            if (PCBvector.at(i).returnArrivalTime() == currentTime)
            {
                Node<PCB> * newNode = new Node<PCB>;
                newNode -> setData(PCBvector.at(i));
                insertPCB(newNode);
                outputFile << currentTime << ". " << PCBvector.at(i).returnProcessName() << " was added to the Ready Queue." << std::endl;
                //Remove the value added to the Queue
                PCBvector.pop_back();
            }
        }

        //If the process has run it's course
        if ((runningProcess != NULL) && (runningProcess -> returnData().returnTimeRemaining() == processRunTime))
        {
            outputFile << currentTime << ". " << runningProcess -> returnData().returnProcessName()
                << " was completed." << std::endl;
            std::cout << "Current Time: " << currentTime << std::endl;
            OSMemory.printMemory();
            OSMemory.removeFromMemory(runningProcess -> returnData().returnProcessName());
            freePCB(runningProcess);
            averageTurnAroundTime = averageTurnAroundTime + currentTime;
            runningProcess = NULL;
        }

        if ((readyQueue.returnTotalNumberOfNodes()) != 0 && (runningProcess == NULL))
        {
            //Add to running process
            runningProcess = readyQueue.returnHeadProcess();
            if ((OSMemory.*InsertionMethod)(runningProcess -> returnData()) == false)
            {
                std::cout << "Process is too big to run on this system" << std::endl;
                return;
            }
            removePCB(runningProcess);
            outputFile << currentTime << ". " << runningProcess -> returnData().returnProcessName()
                << " is now running." << std::endl;
            processRunTime = 0;
        }

        currentTime = currentTime++;
        processRunTime = processRunTime++;
    }

    //Close file
    outputFile.close();
    std::cout << "Average turn Around Time is: " << averageTurnAroundTime/totalProcesses << " seconds." << std::endl;
    std::cout << "Information is saved in FIFO.txt" << std::endl;
    OSMemory.resetMemory();
    return;
}

void processScheduler::STCF(functionPointer InsertionMethod)
{
    std::string fileName;
    std::vector<PCB> PCBvector;
    std::ofstream outputFile;
    outputFile.open("STCF.txt");

    //Ask for file name
    std::cout << "Please input a file name: " << std::endl;
    std::cin >> fileName;
    PCBvector = readProcessesFromFile(fileName);

    //Sort vector based on arrivalTime
    sortVectorByArrivalTime(PCBvector);

    int currentTime = 0;
    int processRunTime = 0;
    int averageTurnAroundTime = 0;
    int totalProcesses = PCBvector.size();
    runningProcess = NULL;

    while ((PCBvector.size() != 0) || (runningProcess != NULL))
    {
        //Travel through the vector and find any programs that must be added to the queue
        for (int i = PCBvector.size()-1; i >= 0; i--)
        {
            //If the process's arrival time is appropriate, add it to the queue and remove from the vector
            if (PCBvector.at(i).returnArrivalTime() == currentTime)
            {
                Node<PCB> * newNode = new Node<PCB>;
                newNode -> setData(PCBvector.at(i));
                insertPCB(newNode);
                outputFile << currentTime << ". " << PCBvector.at(i).returnProcessName() << " was added to the Ready Queue." << std::endl;
                //Remove the value added to the Queue
                PCBvector.pop_back();
            }
        }

        //If the running processes time is down to zero
        if ((runningProcess != NULL) && (runningProcess -> returnData().returnTimeRemaining() <= 0))
        {
            outputFile << currentTime << ". " << runningProcess -> returnData().returnProcessName() << " was completed." << std::endl;
            OSMemory.printMemory();
            OSMemory.removeFromMemory(runningProcess -> returnData().returnProcessName());
            std::cout << "Current Time: " << currentTime << std::endl;
            pauseForUser();
            freePCB(runningProcess);
            runningProcess = NULL;
            averageTurnAroundTime = averageTurnAroundTime + currentTime;
        }

        //If the running process is empty and there are still jobs in the queue
        if ((runningProcess == NULL) && (readyQueue.returnTotalNumberOfNodes() != 0))
        {
            runningProcess = readyQueue.returnLastProcess();
            if (OSMemory.checkExistence(runningProcess -> returnData().returnProcessName()) == false)
            {
                if (((OSMemory.*InsertionMethod)(runningProcess -> returnData())) == false)
                {
                    //Suspend process
                    PCB currentPCB = runningProcess -> returnData();
                    currentPCB.setCurrentState(suspendReady);
                    runningProcess -> setData(currentPCB);
                }
                else
                {
                    readyQueue.removeNode(runningProcess);
                    outputFile << currentTime << ". " << runningProcess -> returnData().returnProcessName() << " is now running" << std::endl;
                }
            }
            else
            {
                readyQueue.removeNode(runningProcess);
                outputFile << currentTime << ". " << runningProcess -> returnData().returnProcessName() << " is now running" << std::endl;
            }
        }

        //If there is a running process and there is jobs in the queue
        //Check for a shorter job
        if ((runningProcess != NULL) && (readyQueue.returnTotalNumberOfNodes() != 0))
        {
            //If there is a shorter job on the queue
            std::vector<PCB> dataVector = readyQueue.returnVector();
            for (int i = 0; i < dataVector.size(); i++)
            {
                if (runningProcess -> returnData().returnTimeRemaining() > dataVector.at(i).returnTimeRemaining())
                {
                    //Replaces process with the lower process
                    if (OSMemory.checkExistence(dataVector.at(i).returnProcessName()) == false)
                    {
                        if ((OSMemory.*InsertionMethod)(dataVector.at(i)) == false)
                        {
                            //Nothing. Let the process continue
                        }
                        else
                        {
                            outputFile << currentTime << ". " << runningProcess -> returnData().returnProcessName() <<
                                " has been paused." << std::endl;
                            insertPCB(runningProcess);
                            runningProcess = readyQueue.removeNode(findPCB(dataVector.at(i).returnProcessName()));
                            outputFile << currentTime << ". " << runningProcess -> returnData().returnProcessName() << " is now running." << std::endl;
                        }
                    }
                    else
                    {
                        outputFile << currentTime << ". " << runningProcess -> returnData().returnProcessName() <<
                            " has been paused." << std::endl;
                        insertPCB(runningProcess);
                        runningProcess = readyQueue.removeNode(findPCB(dataVector.at(i).returnProcessName()));
                        outputFile << currentTime << ". " << runningProcess -> returnData().returnProcessName() << " is now running." << std::endl;
                    }
                }
            }
        }

        if (runningProcess != NULL)
        {
            //Update time remaining on process
            PCB current = runningProcess -> returnData();
            current.setTimeRemaining(current.returnTimeRemaining()-1);
            runningProcess -> setData(current);
        }

        //increment time
        currentTime = currentTime++;
    }

    //Close file
    outputFile.close();
    std::cout << "Average Turn Around Time is: " << averageTurnAroundTime/totalProcesses << " seconds." << std::endl;
    std::cout << "Information is saved in STCF.txt" << std::endl;
    OSMemory.resetMemory();
    return;
}

void processScheduler::FPPS(functionPointer InsertionMethod)
{
    std::string fileName;
    std::vector<PCB> PCBvector;
    std::ofstream outputFile;
    outputFile.open("FPPS.txt");
    Node<PCB> * currentPCB;

    //Ask for file name
    std::cout << "Please input a file name: " << std::endl;
    std::cin >> fileName;
    PCBvector = readProcessesFromFile(fileName);

    //Sort vector based on arrivalTime
    sortVectorByArrivalTime(PCBvector);

    int currentTime = 0;
    int processRunTime = 0;
    int averageTurnAroundTime = 0;
    int totalProcesses = PCBvector.size();
    runningProcess = NULL;


    while ((PCBvector.size() != 0) || (runningProcess != NULL))
    {
        //Travel through the vector and find any programs that must be added to the queue
        for (int i = PCBvector.size()-1; i >= 0; i--)
        {
            //If the process's arrival time is appropriate, add it to the queue and remove from the vector
            if (PCBvector.at(i).returnArrivalTime() == currentTime)
            {
                Node<PCB> * newNode = new Node<PCB>;
                newNode -> setData(PCBvector.at(i));
                insertPCB(newNode);
                outputFile << currentTime << ". " << PCBvector.at(i).returnProcessName() << " was added to the Ready Queue." << std::endl;
                //Remove the value added to the Queue
                PCBvector.pop_back();
            }
        }

        //If the running processes time is down to zero
        if ((runningProcess != NULL) && (runningProcess -> returnData().returnTimeRemaining() <= 0))
        {
            outputFile << currentTime << ". " << runningProcess -> returnData().returnProcessName()
                << " was completed." << std::endl;
            //Print for update before the removal of something
            OSMemory.printMemory();
            pauseForUser();
            //Then Remove
            OSMemory.removeFromMemory(runningProcess -> returnData().returnProcessName());
            freePCB(runningProcess);
            runningProcess = NULL;
            averageTurnAroundTime = averageTurnAroundTime + currentTime;
        }

        //If the running process is empty and there are still jobs in the queue
        if ((runningProcess == NULL) && (readyQueue.returnTotalNumberOfNodes() != 0))
        {
            runningProcess = readyQueue.returnLastProcess();
            readyQueue.removeNode(runningProcess);
            if (OSMemory.checkExistence(runningProcess -> returnData().returnProcessName()) == false)
            {
                if ((OSMemory.*InsertionMethod)(runningProcess-> returnData()) == false)
                {
                    //Leave it empty
                    insertPCB(runningProcess);
                    runningProcess = NULL;
                }
            }
            outputFile << currentTime << ". " << runningProcess -> returnData().returnProcessName() << " is now running" << std::endl;
        }

        //If there is a running process and there is jobs in the queue
        //Check for a higher priority
        if ((runningProcess != NULL) && (readyQueue.returnTotalNumberOfNodes() != 0))
        {
            //If there is a higher priority on the queue
            std::vector<PCB> dataVector = readyQueue.returnVector();
            for (int i = 0; i < dataVector.size(); i++)
            {
                //If there priority of the running process is less than that of th
                if (runningProcess -> returnData().returnPriority() < dataVector.at(i).returnPriority())
                {
                    //Replaces process with the lower process
                    //If it exists in data already
                    if (OSMemory.checkExistence(dataVector.at(i).returnProcessName()) == false)
                    {
                        if ((OSMemory.*InsertionMethod)(dataVector.at(i)) == false)
                        {
                            //Nothing
                        }
                        else
                        {
                            outputFile << currentTime << ". " << runningProcess -> returnData().returnProcessName() << " has been paused." << std::endl;
                            insertPCB(runningProcess);
                            runningProcess = readyQueue.removeNode(findPCB(dataVector.at(i).returnProcessName()));
                            outputFile << currentTime << ". " << runningProcess -> returnData().returnProcessName() << " is now running." << std::endl;
                        }
                    }
                    //Else it already exists in memory, so load it
                    else
                    {
                        outputFile << currentTime << ". " << runningProcess -> returnData().returnProcessName() << " has been paused." << std::endl;
                        insertPCB(runningProcess);
                        runningProcess = readyQueue.removeNode(findPCB(dataVector.at(i).returnProcessName()));
                        outputFile << currentTime << ". " << runningProcess -> returnData().returnProcessName() << " is now running." << std::endl;
                    }
                }
            }
        }

        //Update timer on process
        if (runningProcess != NULL)
        {
            //Update time remaining on process
            PCB current = runningProcess -> returnData();
            current.setTimeRemaining(current.returnTimeRemaining()-1);
            runningProcess -> setData(current);
        }

        //increment time
        currentTime = currentTime++;
    }

    //Close file
    outputFile.close();
    OSMemory.resetMemory();
    averageTurnAroundTime = averageTurnAroundTime/totalProcesses;
    std::cout << "Average Turn Around Time is: " << averageTurnAroundTime << std::endl;
    std::cout << "Information is saved in FPPS.txt" << std::endl;
    return;
}

void processScheduler::roundRobin(functionPointer InsertionMethod)
{
    std::string fileName;
    std::vector<PCB> PCBvector;
    std::ofstream outputFile;
    outputFile.open("RoundRobin.txt");

    Node<PCB> * currentPCB;
    int timeQuantum = 0;

    //Ask for file name
    std::cout << "Please input a file name: " << std::endl;
    std::cin >> fileName;
    PCBvector = readProcessesFromFile(fileName);
    while (timeQuantum < 1)
    {
        std::cout << "Please input a positive integer value for the Time Quantum" << std::endl;
        std::cin >> timeQuantum;
    }

    //Sort vector based on arrivalTime
    sortVectorByArrivalTime(PCBvector);

    int currentTime = 0;
    int processRunTime = 0;
    int averageTurnAroundTime = 0;
    runningProcess = NULL;

    while ((PCBvector.size() != 0) || (runningProcess != NULL))
    {
        //Add Processes as they arrive
        for (int i = PCBvector.size()-1; i >= 0; i--)
        {
            //If the process's arrival time is appropriate, add it to the queue and remove from the vector
            if (PCBvector.at(i).returnArrivalTime() == currentTime)
            {
                Node<PCB> * newNode = new Node<PCB>;
                newNode -> setData(PCBvector.at(i));
                insertPCB(newNode);
                outputFile << currentTime << ". " << PCBvector.at(i).returnProcessName() << " was added to the Ready Queue." << std::endl;
                //Remove the value added to the Queue
                PCBvector.pop_back();
            }
        }

        //If the process is complete
        if (runningProcess != NULL && runningProcess -> returnData().returnTimeRemaining() == 0)
        {
            outputFile << currentTime << ". " << runningProcess -> returnData().returnProcessName()
                << " was completed." << std::endl;
            //Remove it and print current memory
            std::cout << "Current Time: " << currentTime << std::endl;
            OSMemory.printMemory();
            pauseForUser();
            OSMemory.removeFromMemory(runningProcess -> returnData().returnProcessName());
            freePCB(runningProcess);
            runningProcess = NULL;
        }

        if (readyQueue.returnTotalNumberOfNodes() != 0)
        {
            //If there is no currently running process
            if (runningProcess == NULL)
            {
                runningProcess = readyQueue.returnLastProcess();
                //If it doesn't exist in memory
                if (OSMemory.checkExistence(runningProcess -> returnData().returnProcessName()) == false)
                {
                    //If no room
                    if ((OSMemory.*InsertionMethod)(runningProcess -> returnData()) == false)
                    {
                        //Return this thing back to the list. No room.
                        insertPCB(runningProcess);
                        runningProcess = NULL;
                    }
                    //There is room
                    else
                    {
                        removePCB(runningProcess);
                        outputFile << currentTime << ". " << runningProcess -> returnData().returnProcessName() << " is now running." << std::endl;
                    }
                }
                //Run it
                else
                {
                    removePCB(runningProcess);
                    outputFile << currentTime << ". " << runningProcess -> returnData().returnProcessName() << " is now running." << std::endl;
                }
            }
            else
            {
                //If the process has used up it's timeQuantum
                if (currentTime % timeQuantum == 0)
                {
                    outputFile << currentTime << ". " << runningProcess -> returnData().returnProcessName() << " has been paused." << std::endl;
                    insertPCB(runningProcess);
                    runningProcess = readyQueue.returnLastProcess();
                    //If it doesn't exist in data
                    if (OSMemory.checkExistence(runningProcess -> returnData().returnProcessName()) == false)
                    {
                        //If no room
                        if ((OSMemory.*InsertionMethod)(runningProcess -> returnData()) == false)
                        {
                            //Return this thing back to the list. No room.
                            insertPCB(runningProcess);
                            runningProcess = NULL;
                        }
                        //There is room
                        else
                        {
                            removePCB(runningProcess);
                            outputFile << currentTime << ". " << runningProcess -> returnData().returnProcessName() << " is now running." << std::endl;
                        }
                    }
                    else
                    {
                        removePCB(runningProcess);
                        outputFile << currentTime << ". " << runningProcess -> returnData().returnProcessName() << " is now running." << std::endl;
                    }
                }
            }
        }

        //Update time Remaining
        if (runningProcess != NULL)
        {
            //Update time remaining on process
            PCB current = runningProcess -> returnData();
            current.setTimeRemaining(current.returnTimeRemaining()-1);
            runningProcess -> setData(current);
        }

        currentTime = currentTime++;
    }

    //Close file
    outputFile.close();
    OSMemory.resetMemory();
    std::cout << "Information is saved in RoundRobin.txt" << std::endl;
    return;
}

void processScheduler::MLQF()
{
    return;
}

void processScheduler::lottery(functionPointer InsertionMethod)
{
    std::string fileName;
    std::ofstream outputFile;
    std::vector<PCB> PCBvector;
    int tickets = 0;

    outputFile.open("lottery.txt");
    //Ask for file name
    std::cout << "Please input a file name: " << std::endl;
    std::cin >> fileName;
    PCBvector = readProcessesFromFile(fileName);
    while (tickets < 1)
    {
        std::cout << "Please input a positive number of tickets to be used by the processes: " << std::endl;
        std::cin >> tickets;
    }

    //Sort vector based on arrivalTime
    sortVectorByArrivalTime(PCBvector);

    int currentTime = 0;
    int processRunTime = 0;
    int averageTurnAroundTime = 0;
    runningProcess = NULL;

    //Seed for random number generation
    srand(time(NULL));

    while ((PCBvector.size() != 0) || (runningProcess != NULL))
    {
        for (int i = PCBvector.size()-1; i >= 0; i--)
        {
            //If the process's arrival time is appropriate, add it to the queue and remove from the vector
            if (PCBvector.at(i).returnArrivalTime() == currentTime)
            {
                Node<PCB> * newNode = new Node<PCB>;
                newNode -> setData(PCBvector.at(i));
                insertPCB(newNode);
                outputFile << currentTime << ". " << PCBvector.at(i).returnProcessName() << " was added to the Ready Queue." << std::endl;
                //Remove the value added to the Queue
                PCBvector.pop_back();
            }
        }

        //If the process has run it's time, remove it
        if (runningProcess != NULL && runningProcess -> returnData().returnTimeRemaining() == 0)
        {
            outputFile << currentTime << ". " << runningProcess -> returnData().returnProcessName()
                << " was completed." << std::endl;
            OSMemory.printMemory();
            pauseForUser();
            OSMemory.removeFromMemory(runningProcess -> returnData().returnProcessName());
            freePCB(runningProcess);
            runningProcess = NULL;
        }

        //If there is no other nodes in the Queue, continue to run
        if (readyQueue.returnTotalNumberOfNodes() == 0)
        {
            //Let the process run
        }
        else
        {
            //Calculate current process
            std::vector<PCB> CPUVector = readyQueue.returnVector();
            if (CPUVector.size() != 0)
            {
                int TotalCPU = 0;
                sortVectorByCPU(CPUVector);
                int beginningInterval = 0;
                int randomTicket = rand() % tickets;
                //Select random number
                for (int i = 0; i < CPUVector.size(); i++)
                {
                    //If the random number is between the beginning interval and the maximum value for the interval
                    int upperBound = (CPUVector.at(i).returnCPUPercentage()*.01*tickets) + beginningInterval;
                    if (randomTicket < upperBound && randomTicket > beginningInterval)
                    {
                        //Load process
                        if (runningProcess != NULL)
                        {
                            if ((CPUVector.at(i).returnProcessName()) == (runningProcess -> returnData().returnProcessName()))
                            {
                                //Do nothing. The Process is the same.
                                break;
                            }
                            else
                            {
                                outputFile << currentTime << ". " << runningProcess -> returnData().returnProcessName() << " has been paused." << std::endl;
                                insertPCB(runningProcess);
                                runningProcess = readyQueue.removeNode(findPCB(CPUVector.at(i).returnProcessName()));
                                if (OSMemory.checkExistence(runningProcess -> returnData().returnProcessName()) == false)
                                {
                                    if ((OSMemory.*InsertionMethod)(runningProcess -> returnData()) == false)
                                    {
                                        //Return the Process as there isn't enough room for it
                                        insertPCB(runningProcess);
                                        runningProcess = NULL;
                                    }
                                    else
                                    {
                                        outputFile << currentTime << ". " << runningProcess -> returnData().returnProcessName() << " is now running." << std::endl;
                                    }
                                }
                                else
                                {
                                    outputFile << currentTime << ". " << runningProcess -> returnData().returnProcessName() << " is now running." << std::endl;
                                }
                            }
                        }
                        //If it is empty, load her up
                        else
                        {
                            runningProcess = readyQueue.removeNode(findPCB(CPUVector.at(i).returnProcessName()));
                            if (OSMemory.checkExistence(runningProcess -> returnData().returnProcessName()) == false)
                            {
                                if ((OSMemory.*InsertionMethod)(runningProcess -> returnData()) == false)
                                {
                                    //Return the Process as there isn't enough room for it
                                    insertPCB(runningProcess);
                                    runningProcess = NULL;
                                }
                                else
                                {
                                    outputFile << currentTime << ". " << runningProcess -> returnData().returnProcessName() << " is now running." << std::endl;
                                }
                            }
                            else
                            {
                                outputFile << currentTime << ". " << runningProcess -> returnData().returnProcessName() << " is now running." << std::endl;
                            }
                        }
                    }
                    beginningInterval = upperBound;
                }
            }
        }

        //Load up another process if none was selected as a fail safe
        if ((runningProcess == NULL) && readyQueue.returnTotalNumberOfNodes() != 0)
        {
            runningProcess = readyQueue.returnLastProcess();
            if (OSMemory.checkExistence(runningProcess -> returnData().returnProcessName()) == false)
            {
                if ((OSMemory.*InsertionMethod)(runningProcess -> returnData()) == false)
                {
                    //Return the Process as there isn't enough room for it
                    insertPCB(runningProcess);
                    runningProcess = NULL;
                }
                else
                {
                    readyQueue.removeNode(runningProcess);
                    outputFile << currentTime << ". " << runningProcess -> returnData().returnProcessName() << " is now running." << std::endl;
                }
            }
            else
            {
                readyQueue.removeNode(runningProcess);
                outputFile << currentTime << ". " << runningProcess -> returnData().returnProcessName() << " is now running." << std::endl;
            }
        }

        //Update Time on running Process
        if(runningProcess != NULL)
        {
            //Update time remaining on process
            PCB current = runningProcess -> returnData();
            current.setTimeRemaining(current.returnTimeRemaining()-1);
            runningProcess -> setData(current);
        }

        currentTime = currentTime++;
    }

    std::cout << "Information is saved in lottery.txt" << std::endl;
    outputFile.close();
    OSMemory.resetMemory();
    return;
}
