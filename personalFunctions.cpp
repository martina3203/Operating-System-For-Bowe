#include "personalFunctions.h"


//Converts a Given Integer to a String
std::string convertIntToString(int number)
{
    std::string result = "";
    std::ostringstream exchange;
    exchange << number;
    result = exchange.str();
    return result;
}

//Waits for User to Press Enter before continuing
void pauseForUser()
{
    std::cout << "Press Enter to Continue." << std::endl;
    std::cin.ignore();

    return;
}

std::string constructStringToSize(std::string targetString, int sizeOfOutput)
{
    std::string newString = "";
    for (unsigned int h = 0; h < targetString.size(); h++)
    {
        if (newString.size() < sizeOfOutput)
        {
            newString = newString + targetString.at(h);
        }
    }

    //Adds Spaces if Needed
    for (unsigned int i = newString.size(); i < sizeOfOutput; i++)
    {
        newString = newString + " ";
    }


    return newString;
}

void sortVectorByTimeRemaining(std::vector<PCB> &targetVector)
{
    bool sorted = false;
    //Copy vector for the vector passed in
    std::vector<PCB> exchangedVector = targetVector;
    //While this flag is false
    while (sorted == false)
    {
        //Reset flag
        sorted = true;
        for (unsigned int i = 0; i < targetVector.size()-1; i++)
        {
            //If the first PCB Time Remaining is Less than the next
            if ((exchangedVector.at(i).returnTimeRemaining()) < (exchangedVector.at(i+1).returnTimeRemaining()))
            {
                PCB savedPCB = exchangedVector.at(i);
                exchangedVector.at(i) = exchangedVector.at(i+1);
                exchangedVector.at(i+1) = savedPCB;
                sorted = false;
            }
        }
        //Copy the new vector over
    }
    targetVector = exchangedVector;
    return;
}

void sortVectorByArrivalTime(std::vector<PCB> &targetVector)
{
    bool sorted = false;
    //Copy vector for the vector passed in
    std::vector<PCB> exchangedVector = targetVector;
    //While this flag is false
    while (sorted == false)
    {
        //Reset flag
        sorted = true;
        for (unsigned int i = 0; i < targetVector.size()-1; i++)
        {
            //If the first PCB Arrival Time is Less than the next
            if ((exchangedVector.at(i).returnArrivalTime()) < (exchangedVector.at(i+1).returnArrivalTime()))
            {
                PCB savedPCB = exchangedVector.at(i);
                exchangedVector.at(i) = exchangedVector.at(i+1);
                exchangedVector.at(i+1) = savedPCB;
                sorted = false;
            }
        }
        //Copy the new vector over
    }
    targetVector = exchangedVector;
    return;
}

void sortVectorByPriority(std::vector<PCB> &targetVector)
{
    bool sorted = false;
    //Copy vector for the vector passed in
    std::vector<PCB> exchangedVector = targetVector;
    //While this flag is false
    while (sorted == false)
    {
        //Reset flag
        sorted = true;
        for (unsigned int i = 0; i < targetVector.size()-1; i++)
        {
            //If the first PCB Priority is Greater than the next
            if ((exchangedVector.at(i).returnPriority()) > (exchangedVector.at(i+1).returnPriority()))
            {
                PCB savedPCB = exchangedVector.at(i);
                exchangedVector.at(i) = exchangedVector.at(i+1);
                exchangedVector.at(i+1) = savedPCB;
                sorted = false;
            }
        }
        //Copy the new vector over
    }
    targetVector = exchangedVector;
    return;
}

void sortVectorByCPU(std::vector<PCB> &targetVector)
{
    bool sorted = false;
    //Copy vector for the vector passed in
    std::vector<PCB> exchangedVector = targetVector;
    //While this flag is false
    while (sorted == false)
    {
        //Reset flag
        sorted = true;
        for (unsigned int i = 0; i < targetVector.size()-1; i++)
        {
            //If the first PCB Priority is Greater than the next
            if ((exchangedVector.at(i).returnCPUPercentage()) < (exchangedVector.at(i+1).returnCPUPercentage()))
            {
                PCB savedPCB = exchangedVector.at(i);
                exchangedVector.at(i) = exchangedVector.at(i+1);
                exchangedVector.at(i+1) = savedPCB;
                sorted = false;
            }
        }
        //Copy the new vector over
    }
    targetVector = exchangedVector;
    return;

}


functionPointer returnMemoryInsertionMethod()
{
    std::cout << "Select Memory Method: " << std::endl;
    std::cout << "1. First Fit " << "2. Next Fit " << "3. Best Fit " << "4. Worst Fit" << std::endl;
    functionPointer returnedPointer;
    int input;
    while (input < 1)
    {
        std::cin >> input;
        switch (input)
        {
            case 1:
                returnedPointer = &memoryManager::insertFirstFit;
                break;
            case 2:
                returnedPointer = &memoryManager::insertNextFit;
                break;
            case 3:
                returnedPointer = &memoryManager::insertBestFit;
                break;
            case 4:
                returnedPointer = &memoryManager::insertWorstFit;
                break;
            default:
                std::cout << "Invalid Input" << std::endl;
                input = 0;
                break;
        }
    }
    /*
    memoryManager newManager;
    PCB newPCB("HI");
    std::cout << (newManager.*returnedPointer)(newPCB);
    */
    return returnedPointer;
}
