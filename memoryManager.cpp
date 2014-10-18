#include "memoryManager.h"

memorySegment::memorySegment()
{
    //Constructor
    nextSegment = NULL;
}

PCB memorySegment::returnPCB()
{
    return theProcess;
}

int memorySegment::returnStartLocation()
{
    return startingLocation;
}

int memorySegment::returnEndLocation()
{
    return endingLocation;
}

memorySegment * memorySegment::returnNextSegment()
{
    return nextSegment;
}

void memorySegment::setPCB(PCB newProcess)
{
    theProcess = newProcess;
}

void memorySegment::setStartLocation(int start)
{
    startingLocation = start;
}

void memorySegment::setEndLocation(int End)
{
    endingLocation = End;
}

void memorySegment::setNextSegment(memorySegment * newSegment)
{
    nextSegment = newSegment;
}



memoryManager::memoryManager()
{
    freeListHeadNode = new memorySegment;
    PCB freeProcessTemplate("FREE");
    freeListHeadNode -> setPCB(freeProcessTemplate);
    freeListHeadNode -> setStartLocation(0);
    freeListHeadNode -> setEndLocation(1023);
    freeListHeadNode -> setNextSegment(NULL);

    occupiedListHeadNode = NULL;
}

memoryManager::~memoryManager()
{
    //Clear up free list
    memorySegment * traverse = freeListHeadNode;
    while (traverse != NULL)
    {
        memorySegment * currentSegment = traverse;
        traverse = traverse -> returnNextSegment();
        delete currentSegment;
        currentSegment = NULL;
    }

    traverse = occupiedListHeadNode;
    //Clear up Occupied LIst
    while (traverse != NULL)
    {
        memorySegment * currentSegment = traverse;
        traverse = traverse -> returnNextSegment();
        delete currentSegment;
        currentSegment = NULL;
    }
}

void memoryManager::test()
{
    PCB testPCB("Poop");
    PCB AnotherPCB("Hey");
    testPCB.setMemoryNeeded(100);
    AnotherPCB.setMemoryNeeded(200);
    insertFirstFit(testPCB);
    insertFirstFit(AnotherPCB);
    removeFromMemory("Poop");
    insertFirstFit(AnotherPCB);
    removeFromMemory("Hey");
    collesceMemory();
    compactMemory();
    //insertFirstFit(testPCB);
    printMemory();
    return;
}

void memoryManager::printMemory()
{
    memorySegment * traverse = occupiedListHeadNode;
    while (traverse != NULL)
    {
        std::cout << traverse -> returnStartLocation() << "-" << traverse -> returnEndLocation() << " ";
        //Print Name then new line
        std::cout << traverse -> returnPCB().returnProcessName() << std::endl;
        traverse = traverse -> returnNextSegment();
    }
    traverse = freeListHeadNode;
    while (traverse != NULL)
    {
        std::cout << traverse -> returnStartLocation() << "-" << traverse -> returnEndLocation() << " ";
        //Print Name then new line
        std::cout << traverse -> returnPCB().returnProcessName() << std::endl;
        traverse = traverse -> returnNextSegment();
    }
}

void memoryManager::addToOccupiedList(memorySegment * newSegment)
{
    if (occupiedListHeadNode == NULL)
    {
        //New Segment becomes the head node
        occupiedListHeadNode = newSegment;
    }
    else
    {
        memorySegment * traverse = occupiedListHeadNode;
        memorySegment * previous = NULL;
        //Traverse the list until we find a spot
        if (newSegment -> returnEndLocation() < occupiedListHeadNode -> returnStartLocation())
        {
            newSegment -> setNextSegment(occupiedListHeadNode);
            occupiedListHeadNode = newSegment;
            return;
        }
        while (traverse -> returnNextSegment() != NULL)
        {
            //If we find a node whose starting point is greater than the segment
            if ((newSegment -> returnEndLocation()) < (traverse -> returnStartLocation()))
            {
                if ((newSegment -> returnStartLocation()) > (previous -> returnEndLocation()))
                {
                    newSegment -> setNextSegment(traverse);
                    previous -> setNextSegment(newSegment);
                    return;
                }
            }
            previous = traverse;
            traverse = traverse -> returnNextSegment();
        }

        //If it gets this far, we add this node to the end of the list
        traverse -> setNextSegment(newSegment);
        newSegment -> setNextSegment(NULL);
    }
    return;
}

void memoryManager::addToFreeList(memorySegment * newSegment)
{
    //Copy Over PCB
    PCB newPCB("FREE");
    newSegment -> setPCB(newPCB);
    if (freeListHeadNode == NULL)
    {
        //New Segment becomes the head node
        freeListHeadNode = newSegment;
        newSegment -> setNextSegment(NULL);
        return;
    }
    else
    {
        memorySegment * traverse = freeListHeadNode;
        memorySegment * previous = NULL;
        //Traverse the list until we find a spot
        if (newSegment -> returnEndLocation() < freeListHeadNode -> returnStartLocation())
        {
            newSegment -> setNextSegment(freeListHeadNode);
            freeListHeadNode = newSegment;
            return;
        }
        while (traverse != NULL)
        {
            if (traverse -> returnStartLocation() > newSegment -> returnEndLocation())
            {
                if (previous != NULL)
                {
                    if (previous -> returnEndLocation() < newSegment -> returnStartLocation())
                    {
                        previous -> setNextSegment(newSegment);
                        newSegment -> setNextSegment(traverse);
                        return;
                    }
                }
            }
            previous = traverse;
            traverse = traverse -> returnNextSegment();
        }
        traverse -> setNextSegment(newSegment);
        newSegment -> setNextSegment(NULL);
    }
    return;
}

bool memoryManager::insertFirstFit(PCB runningProcess)
{
    bool processAdded = false;
    int memoryNeeded = runningProcess.returnAmountOfMemory();
    //Find a free spot in memory that will fit first
    memorySegment * traverse = freeListHeadNode;
    while (traverse != NULL)
    {
        memorySegment * previousNode;
        if ((traverse -> returnEndLocation() - traverse -> returnStartLocation()) >= memoryNeeded)
        {
            memorySegment * newSegment = new memorySegment;
            newSegment -> setPCB(runningProcess);
            newSegment -> setStartLocation(traverse -> returnStartLocation());
            //Change the end location to be just before the free segment starts
            newSegment -> setEndLocation((newSegment -> returnStartLocation()) + memoryNeeded - 1);
            //Add to list
            addToOccupiedList(newSegment);

            //Change current node to reflect the addition of a process
            traverse -> setStartLocation(newSegment-> returnEndLocation()+1);
            //IF this segment is the same in start and end
            if (traverse -> returnStartLocation() == traverse -> returnEndLocation())
            {
                std::cout << "Block is depleted. Deleting." << std::endl;
                if (previousNode != NULL)
                {
                    //Connect previous node to the node following traverse to continue to coke line
                    previousNode -> setNextSegment(traverse -> returnNextSegment());
                }
                delete traverse;
            }
            processAdded = true;
            return processAdded;
        }
        previousNode = traverse;
        traverse = traverse -> returnNextSegment();
    }
    //Else
    //Collasece and try again
    //If that doesn't work, compact and try again
    //If still unsuccesfful, return false

    return false;
}

void memoryManager::removeFromMemory(std::string processName)
{
    memorySegment * traverse = occupiedListHeadNode;
    memorySegment * previous = NULL;
    //Traverse list
    while (traverse != NULL)
    {
        //If we find the process
        if (traverse -> returnPCB().returnProcessName() == processName)
        {
            //If the process happens to be the head node
            if (traverse == occupiedListHeadNode)
            {
                occupiedListHeadNode = traverse -> returnNextSegment();
                traverse -> setNextSegment(NULL);
                addToFreeList(traverse);
                return;
            }
            //Else we connect the previous process to the following process and remove
            else
            {
                previous -> setNextSegment(traverse -> returnNextSegment());
                traverse -> setNextSegment(NULL);
                addToFreeList(traverse);
                return;
            }
        }
        previous = traverse;
        traverse = traverse -> returnNextSegment();
    }
    std::cout << "Process does not exist in Memory" << std::endl;
    return;
}

void memoryManager::compactMemory()
{
    //Eliminate the Free Table
    memorySegment * traverse = freeListHeadNode;
    while (traverse != NULL)
    {
        memorySegment * currentSegment = traverse;
        traverse = traverse -> returnNextSegment();
        delete currentSegment;
        currentSegment = NULL;
    }
    freeListHeadNode = NULL;

    traverse = occupiedListHeadNode;
    int currentPosition = 0;
    while (traverse != NULL)
    {
        //Change the location of each node to fit at the next available position
        traverse -> setStartLocation(currentPosition);
        currentPosition = currentPosition + (traverse-> returnPCB().returnAmountOfMemory()) - 1;
        traverse -> setEndLocation(currentPosition);
        traverse = traverse -> returnNextSegment();
    }
    //Reallcoate for the free spaces
    memorySegment * newFreeSegment = new memorySegment;
    newFreeSegment -> setStartLocation(currentPosition+1);
    newFreeSegment -> setEndLocation(1033);
    newFreeSegment -> setNextSegment(NULL);
    addToFreeList(newFreeSegment);
    return;
}

void memoryManager::collesceMemory()
{
    memorySegment * traverse = freeListHeadNode;

    while (traverse != NULL)
    {
        memorySegment * nextNode = traverse -> returnNextSegment();
        if (nextNode != NULL)
        {
            //If the end location is one away from the being the nextNode's starting location
            if ((traverse -> returnEndLocation()+1) == nextNode -> returnStartLocation())
            {
                //SLAM THEM
                //Change the end point of this segment to match the ending of the next
                traverse -> setEndLocation(nextNode -> returnEndLocation());
                //Then delete the next node
                traverse -> setNextSegment(nextNode -> returnNextSegment());
                delete nextNode;
                nextNode = NULL;
            }
        }
        traverse = traverse -> returnNextSegment();

    }
    return;
}
