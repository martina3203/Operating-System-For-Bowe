#ifndef PERSONALFUNCTIONS_H
#define PERSONALFUNCTIONS_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "PCB.h"
#include "memoryManager.h"

//Define a type that is a function pointer
typedef bool (memoryManager::*functionPointer)(PCB);

std::string convertIntToString(int number);

void pauseForUser();

std::string constructStringToSize(std::string targetString, int sizeOfOutput);

void sortVectorByTimeRemaining(std::vector<PCB> &targetVector);

void sortVectorByArrivalTime(std::vector<PCB> &targetVector);

void sortVectorByPriority(std::vector<PCB> &targetVector);

void sortVectorByCPU(std::vector<PCB> &targetVector);

functionPointer returnMemoryInsertionMethod();

#endif // PERSONALFUNCTIONS_CPP
