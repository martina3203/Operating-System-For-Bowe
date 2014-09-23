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

#endif // PERSONALFUNCTIONS_CPP
