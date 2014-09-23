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
    std::string dumbyVariable;
    std::cout << "Press Enter to Continue." << std::endl;
    getline(std::cin,dumbyVariable);

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
            //If the first PCB Arrival Time is Greater than the next
            if ((exchangedVector.at(i).returnTimeRemaining()) > (exchangedVector.at(i+1).returnTimeRemaining()))
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
