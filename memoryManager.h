#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#define SIZE_OF_MEMORY 1024
#include <string>
#include <ostream>
#include "PCB.h"



class memoryManager
{
    public:
        memoryManager();
        virtual ~memoryManager();
        void printMemory();
        void test();
        bool insertFirstFit(PCB runningProcess);
        bool insertNextFit();
        bool insertBestFit();
        bool insertWorstFit();
        void removeFromMemory(std::string processName);
        void collesceMemory();
        void compactMemory();
    protected:
    private:
        PCB * memoryLocation[SIZE_OF_MEMORY];
        int savedAddress;
};

#endif // MEMORYMANAGER_H
