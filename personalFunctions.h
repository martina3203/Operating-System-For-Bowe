#ifndef PERSONALFUNCTIONS_H
#define PERSONALFUNCTIONS_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "PCB.h"

std::string convertIntToString(int number);

void pauseForUser();

std::string constructStringToSize(std::string targetString, int sizeOfOutput);

void sortVectorByTimeRemaining(std::vector<PCB> &targetVector);

void sortVectorByArrivalTime(std::vector<PCB> &targetVector);

void sortVectorByPriority(std::vector<PCB> &targetVector);

void sortVectorByCPU(std::vector<PCB> &targetVector);

int findMaxTicketCount(std::vector<PCB> &targetVector, int totalTickets);

#endif // PERSONALFUNCTIONS_CPP
