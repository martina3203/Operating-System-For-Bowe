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
