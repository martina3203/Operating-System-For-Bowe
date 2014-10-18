#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#define SIZE_OF_MEMORY 1024
#include <string>
#include <ostream>
#include "PCB.h"


class memorySegment
{
public:
    memorySegment();
    PCB returnPCB();
    int returnStartLocation();
    int returnEndLocation();
    memorySegment * returnNextSegment();
    void setPCB(PCB newProcess);
    void setStartLocation(int start);
    void setEndLocation(int End);
    void setNextSegment(memorySegment * newNextNode);
private:
    PCB theProcess;
    int startingLocation;
    int endingLocation;
    memorySegment * nextSegment;
};

class memoryManager
{
    public:
        memoryManager();
        virtual ~memoryManager();
        void printMemory();
        void test();
        bool insertFirstFit(PCB runningProcess);
        bool insertNextFit(PCB runningProcess);
        bool insertBestFit(PCB runningProcess);
        bool insertWorstFit(PCB runningProcess);
        void removeFromMemory(std::string processName);
        void collesceMemory();
        void compactMemory();
    protected:
    private:
        void addToOccupiedList(memorySegment *);
        void addToFreeList(memorySegment *);
        //Head nodes to linked list
        memorySegment * occupiedListHeadNode;
        memorySegment * freeListHeadNode;
        //These are used in the nextFit function
        memorySegment * savedLocation;
        memorySegment * previousToSavedLocation;
};

#endif // MEMORYMANAGER_H
