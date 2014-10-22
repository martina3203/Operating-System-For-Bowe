#include "OSInfo.h"
#include <time.h>


OSInfo::OSInfo()
{
    //Constructor
    OSName = "Blue Screen Simulator 2014";
    versionNumber = .95832;
}

OSInfo::~OSInfo()
{
    //Destructor
}


std::string OSInfo::returnOSInfo(command request)
{
    std::string returnedInformation = "";
    std::string currentKeyword = request.returnCommandKeyword();
    std::string secondaryInformation = request.returnTargetInformation();

    if (currentKeyword == "show" && secondaryInformation == "time")
    {
        //Credit to http://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
        std::time_t currentTime = std::time(0);
        struct tm * timePointer = std::localtime(&currentTime);

        //Changes Numbers into strings
        returnedInformation = "The Time is ";
        std::string hour = convertIntToString(timePointer -> tm_hour);
        std::string minute = convertIntToString(timePointer -> tm_min);
        std::string second = convertIntToString(timePointer -> tm_sec);

        //Create new string
        returnedInformation = returnedInformation + hour;
        returnedInformation = returnedInformation + ":" + minute + ":" + second;
    }
    else if (currentKeyword == "show" && secondaryInformation == "date")
    {
        //Credit to http://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
        std::time_t currentTime = std::time(0);
        struct tm * timePointer = std::localtime(&currentTime);

        //Changes Numbers to Strings
        if (date == "")
        {
            returnedInformation = "The Date is ";
            std::string month = convertIntToString(timePointer -> tm_mon);
            std::string day = convertIntToString(timePointer -> tm_mday);
            std::string year = convertIntToString(timePointer -> tm_year + 1900);

            //Create new string
            returnedInformation = returnedInformation + month;
            returnedInformation = returnedInformation + "/" + day + "/" + year;
            return returnedInformation;
        }
        else
        {
            returnedInformation = "The Date is " + date;
            return returnedInformation;
        }
    }

    return returnedInformation;
}

std::string OSInfo::returnOSName()
{
    return OSName;
}

void OSInfo::setDate()
{
    int input;
    char charInput;
    std::string newDate = "";

    std::cout << "Please input the current month in numerical form:" <<std::endl;
    std::cin >> input;
    newDate = newDate + convertIntToString(input);



    std::cout << "Please set the current day in numerical form:" <<std::endl;
    std::cin >> input;
    newDate = newDate + "/" + convertIntToString(input);


    std::cout << "Please set the current year in numerical form:" << std::endl;
    std::cin >> input;
    newDate = newDate + "/" + convertIntToString(input);

    std::cout << "Is this the correct date you want? " << newDate << " Y/N?" << std::endl;
    std::cin >> charInput;
    if (charInput == 'Y' || charInput == 'y')
    {
        date = newDate;
    }
    //Clears buffer
    std::cin.ignore();

    return;
}

float OSInfo::returnVersionNumber()
{
    return versionNumber;
}

void OSInfo::test()
{
    command testCommand("show time");
    command secondCommand("show date");

    std::cout << returnOSInfo(testCommand) << std::endl;
    std::cout << returnOSInfo(secondCommand) << std::endl;
    return;
}
