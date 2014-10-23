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
    savedLocation = freeListHeadNode;
    previousToSavedLocation = NULL;
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
    testPCB.setMemoryNeeded(512);
    AnotherPCB.setMemoryNeeded(512);
    insertWorstFit(testPCB);
    insertWorstFit(AnotherPCB);
    printMemory();
    return;
}

void memoryManager::printMemory()
{
    std::cout << "CURRENT MEMORY LISTING:" << std::endl;
    memorySegment * occupiedTraverse = occupiedListHeadNode;
    memorySegment * freeTraverse = freeListHeadNode;
    while (occupiedTraverse != NULL || freeTraverse != NULL)
    {
        if (occupiedTraverse != NULL && freeTraverse != NULL)
        {
            if (occupiedTraverse -> returnStartLocation() < freeTraverse -> returnStartLocation())
            {
                std::cout << occupiedTraverse -> returnStartLocation() << "-" << occupiedTraverse -> returnEndLocation() << " ";
                std::cout << occupiedTraverse -> returnPCB().returnProcessName() << std::endl;
                occupiedTraverse = occupiedTraverse -> returnNextSegment();
            }
            else
            {
                std::cout << freeTraverse -> returnStartLocation() << "-" << freeTraverse -> returnEndLocation() << " ";
                std::cout << "FREE" << std::endl;
                freeTraverse = freeTraverse -> returnNextSegment();
            }
        }
        else
        {
            if (occupiedTraverse != NULL)
            {
                std::cout << occupiedTraverse -> returnStartLocation() << "-" << occupiedTraverse -> returnEndLocation() << " ";
                std::cout << occupiedTraverse -> returnPCB().returnProcessName() << std::endl;
                occupiedTraverse = occupiedTraverse -> returnNextSegment();
            }
            if (freeTraverse != NULL)
            {
                std::cout << freeTraverse -> returnStartLocation() << "-" << freeTraverse -> returnEndLocation() << " ";
                std::cout << "FREE" << std::endl;
                freeTraverse = freeTraverse -> returnNextSegment();
            }
        }
    }
    return;
}

bool memoryManager::checkExistence(std::string processName)
{
    memorySegment * traverse = occupiedListHeadNode;
    while (traverse != NULL)
    {
        if (traverse -> returnPCB().returnProcessName() == processName)
        {
            return true;
        }
        traverse = traverse -> returnNextSegment();
    }
    return false;
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
    bool compactionCompleted = false;
    bool collesceCompleted = false;
    bool triedEverything = false;
    int memoryNeeded = runningProcess.returnAmountOfMemory();
    //Find a free spot in memory that will fit first
    memorySegment * traverse = freeListHeadNode;

    while (triedEverything == false)
    {
        memorySegment * previousNode = NULL;
        while (traverse != NULL)
        {
            if ((traverse -> returnEndLocation() - traverse -> returnStartLocation()+1) >= memoryNeeded)
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
                if (traverse -> returnStartLocation() > traverse -> returnEndLocation())
                {
                    std::cout << "Block is depleted. Deleting." << std::endl;
                    if (previousNode != NULL)
                    {
                        //Connect previous node to the node following traverse to continue to coke line
                        previousNode -> setNextSegment(traverse -> returnNextSegment());
                    }
                    else if (traverse == freeListHeadNode)
                    {
                        freeListHeadNode = traverse -> returnNextSegment();
                    }
                    delete traverse;
                    traverse = NULL;
                }
                processAdded = true;
                return processAdded;
            }
            previousNode = traverse;
            traverse = traverse -> returnNextSegment();
        }
        //Try collesce if we are unable to add yet
        collesceMemory();
        //If that doesn't work, use compaction and try again
        if (collesceCompleted == true)
        {
            compactMemory();
            //If we have already tried compaction
            if (compactionCompleted == true)
            {
                triedEverything = true;
            }
            compactionCompleted = true;
        }
        collesceCompleted = true;
    }
    return false;
}

bool memoryManager::insertNextFit(PCB runningProcess)
{
    bool processAdded = false;
    bool compactionCompleted = false;
    bool collesceCompleted = false;
    bool triedEverything = false;

    int memoryNeeded = runningProcess.returnAmountOfMemory();
    //Find a free spot in memory that will fit after the next saved node
    memorySegment * traverse = savedLocation;
    memorySegment * previous = previousToSavedLocation;

    while (triedEverything == false)
    {
        //While traversing the list and finishing when we come around the full loop
        while (traverse -> returnNextSegment() != savedLocation)
        {
            //If the segment is big enough
            if ((traverse -> returnEndLocation() - traverse -> returnStartLocation()+1) >= memoryNeeded)
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
                if (traverse -> returnStartLocation() > traverse -> returnEndLocation())
                {
                    std::cout << "Block is depleted. Deleting." << std::endl;
                    if (previous != NULL)
                    {
                        //Connect previous node to the node following traverse to continue to coke line
                        previous -> setNextSegment(traverse -> returnNextSegment());
                        savedLocation = previous -> returnNextSegment();
                        previousToSavedLocation = previous;
                    }
                    else
                    {
                        savedLocation = traverse -> returnNextSegment();
                        previousToSavedLocation = NULL;
                    }
                    //If this node is the headpointer, save the next location as the head node
                    if (traverse == freeListHeadNode)
                    {
                        freeListHeadNode = traverse -> returnNextSegment();
                    }
                    delete traverse;
                    traverse = NULL;
                }
                else
                {
                    //Save our last addresses for the next run of this function
                    savedLocation = traverse;
                    previousToSavedLocation = previous;
                }
                processAdded = true;
                return processAdded;
            }
            //If we are at the end of the list, start back at the beginning of the list
            if (traverse -> returnNextSegment() == NULL)
            {
                previous = NULL;
                traverse = freeListHeadNode;
            }
            else
            {
                previous = traverse;
                traverse = traverse -> returnNextSegment();
            }
        }
        //Try collesce if we are unable to add yet
        collesceMemory();
        //If that doesn't work, use compaction and try again
        if (collesceCompleted == true)
        {
            compactMemory();
            //If we have already tried compaction
            if (compactionCompleted == true)
            {
                triedEverything = true;
            }
            compactionCompleted = true;
        }
        collesceCompleted = true;
    }
    return false;
}

bool memoryManager::insertBestFit(PCB runningProcess)
{
    bool processAdded = false;
    bool compactionCompleted = false;
    bool collesceCompleted = false;
    bool triedEverything = false;

    int memoryNeeded = runningProcess.returnAmountOfMemory();
    int bestFitSize = 1024;
    memorySegment * traverse = freeListHeadNode;
    memorySegment * previous = NULL;
    memorySegment * bestSegment = NULL;
    memorySegment * beforeBestSegment = NULL;

    while (triedEverything == false)
    {
        while (traverse != NULL)
        {
            //If this node is smaller than the current best size
            int segmentSize = traverse -> returnEndLocation() - traverse -> returnStartLocation()+1;
            if (segmentSize >= memoryNeeded)
            {
                //If this segment is of the best fit for the new segment
                if (segmentSize < bestFitSize)
                {
                    //Make this the current best segment to allocate to
                    bestFitSize = segmentSize;
                    bestSegment = traverse;
                    beforeBestSegment = previous;
                }
            }
            previous = traverse;
            traverse = traverse -> returnNextSegment();
        }
        //if the point is not NULL
        if (bestSegment != NULL)
        {
            //Allocate memory for the process
            memorySegment * newSegment = new memorySegment;
            newSegment -> setPCB(runningProcess);
            newSegment -> setStartLocation(bestSegment -> returnStartLocation());
            //Change the end location to be just before the free segment starts
            newSegment -> setEndLocation((newSegment -> returnStartLocation()) + memoryNeeded - 1);
            //Add to list
            addToOccupiedList(newSegment);
            //Change current node to reflect the addition of a process
            bestSegment -> setStartLocation(newSegment-> returnEndLocation()+1);
            //IF this segment is the same in start and end
            if (bestSegment -> returnStartLocation() > bestSegment -> returnEndLocation())
            {
                std::cout << "Block is depleted. Deleting." << std::endl;
                if (beforeBestSegment != NULL)
                {
                    //Connect previous node to the node following traverse to continue to coke line
                    beforeBestSegment -> setNextSegment(bestSegment -> returnNextSegment());
                }
                if (bestSegment == freeListHeadNode)
                {
                    freeListHeadNode = bestSegment -> returnNextSegment();
                }
                delete bestSegment;
                bestSegment = NULL;
            }
            processAdded = true;
            return processAdded;
        }
        //Else
        //Try collesce if we are unable to add yet
        collesceMemory();
        //If that doesn't work, use compaction and try again
        if (collesceCompleted == true)
        {
            compactMemory();
            //If we have already tried compaction
            if (compactionCompleted == true)
            {
                triedEverything = true;
            }
            compactionCompleted = true;
        }
        collesceCompleted = true;
    }
    return false;
}

bool memoryManager::insertWorstFit(PCB runningProcess)
{
    bool processAdded = false;
    bool compactionCompleted = false;
    bool collesceCompleted = false;
    bool triedEverything = false;

    int memoryNeeded = runningProcess.returnAmountOfMemory();
    int worstFitSize = 0;
    memorySegment * traverse = freeListHeadNode;
    memorySegment * previous = NULL;
    memorySegment * worstSegment = NULL;
    memorySegment * beforeWorstSegment = NULL;

    while (triedEverything == false)
    {
        while (traverse != NULL)
        {
            //If this node is smaller than the current best size
            int segmentSize = traverse -> returnEndLocation() - traverse -> returnStartLocation()+1;
            if (segmentSize >= memoryNeeded)
            {
                //If this segment is of the best fit for the new segment
                if (segmentSize > worstFitSize)
                {
                    //Make this the current best segment to allocate to
                    worstFitSize = segmentSize;
                    worstSegment = traverse;
                    beforeWorstSegment = previous;
                }
            }
            previous = traverse;
            traverse = traverse -> returnNextSegment();
        }
        //if the point is not NULL
        if (worstSegment != NULL)
        {
            //Allocate memory for the process
            memorySegment * newSegment = new memorySegment;
            newSegment -> setPCB(runningProcess);
            newSegment -> setStartLocation(worstSegment -> returnStartLocation());
            //Change the end location to be just before the free segment starts
            newSegment -> setEndLocation((newSegment -> returnStartLocation()) + memoryNeeded - 1);
            //Add to list
            addToOccupiedList(newSegment);
            //Change current node to reflect the addition of a process
            worstSegment -> setStartLocation(newSegment-> returnEndLocation()+1);
            //IF this segment is the same in start and end
            if (worstSegment -> returnStartLocation() > worstSegment -> returnEndLocation())
            {
                std::cout << "Block is depleted. Deleting." << std::endl;
                if (beforeWorstSegment != NULL)
                {
                    //Connect previous node to the node following traverse to continue to coke line
                    beforeWorstSegment -> setNextSegment(worstSegment -> returnNextSegment());
                }
                if (worstSegment == freeListHeadNode)
                {
                    freeListHeadNode = worstSegment -> returnNextSegment();
                }
                delete worstSegment;
                worstSegment = NULL;
            }
            processAdded = true;
            return processAdded;
        }
        //Else
        //Try collesce if we are unable to add yet
        collesceMemory();
        //If that doesn't work, use compaction and try again
        if (collesceCompleted == true)
        {
            compactMemory();
            //If we have already tried compaction
            if (compactionCompleted == true)
            {
                triedEverything = true;
            }
            compactionCompleted = true;
        }
        collesceCompleted = true;
    }
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
    newFreeSegment -> setEndLocation(1023);
    newFreeSegment -> setNextSegment(NULL);
    addToFreeList(newFreeSegment);
    //Reset pointers for the NextFit function
    savedLocation = freeListHeadNode;
    previousToSavedLocation = NULL;
    return;
}

void memoryManager::collesceMemory()
{
    memorySegment * traverse = freeListHeadNode;
    memorySegment * previous = NULL;

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
                //This resets flags if they were somehow lost
                if (nextNode == savedLocation)
                {
                    savedLocation = traverse;
                    previousToSavedLocation = previous;
                }
                delete nextNode;
                nextNode = NULL;
            }
        }
        previous = traverse;
        traverse = traverse -> returnNextSegment();

    }
    return;
}

void memoryManager::resetMemory()
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

    freeListHeadNode = new memorySegment;
    PCB freeProcessTemplate("FREE");
    freeListHeadNode -> setPCB(freeProcessTemplate);
    freeListHeadNode -> setStartLocation(0);
    freeListHeadNode -> setEndLocation(1023);
    freeListHeadNode -> setNextSegment(NULL);

    occupiedListHeadNode = NULL;
    savedLocation = freeListHeadNode;
    previousToSavedLocation = NULL;


    return;
}
