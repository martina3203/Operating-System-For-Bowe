#include "OS.h"
#include "OSInfo.h"
#include <dirent.h>

OS::OS()
{
    //Constructor
}

OS::~OS()
{
    //Destructor
}

void OS::execute()
{
    //Brings up starting info
    startScreen();
    std::string newInput;
    //Accepts commands
    while (newInput != "exit")
    {
        std::cout << "Input? -> ";
        getline(std::cin, newInput);
        command userCommand(newInput);
        OSCommandHistory.addCommand(userCommand);
        if (userCommand.returnValidCommand() == true)
        {
            executeOrder(userCommand);
        }
        else if (newInput != "exit")
        {
            std::cout << "Invalid Command" << std::endl;
        }

    }

    return;
}

void OS::startScreen()
{
    std::cout << systemInfo.returnOSName() << "                     Version Number: " << systemInfo.returnVersionNumber() << std::endl << std::endl << std::endl;

    return;
}

void OS::executeOrder(command newCommand)
{
    //Saves copy of order into local variables for easy reading
    std::string returnedInformation = "";
    std::string secondaryInformation = newCommand.returnTargetInformation();
    std::string keyword = newCommand.returnCommandKeyword();


    if (keyword == "show")
    {
        //Converts seconddary information to lower case for easier understanding
        newCommand.convert(2);
        secondaryInformation = newCommand.returnTargetInformation();

        if (secondaryInformation == "time")
        {
            returnedInformation = systemInfo.returnOSInfo(newCommand);
            std::cout << returnedInformation << std::endl << std::endl;
        }
        else if (secondaryInformation == "date")
        {
            returnedInformation = systemInfo.returnOSInfo(newCommand);
            std::cout << returnedInformation << std::endl << std::endl;
        }
        else if (secondaryInformation == "version")
        {
            std::cout << "Current Version: " << systemInfo.returnVersionNumber() << std::endl << std::endl;
        }
        else if (secondaryInformation == "directory")
        {
            accessDirectory("\\");
        }
        else
        {
            std::cout << "Unknown Target of Command. Please restate." << std::endl << std::endl;
        }
    }
    else if (keyword == "print")
    {
        newCommand.convert(2);
        secondaryInformation = newCommand.returnTargetInformation();
        if (secondaryInformation == "previouscommands")
        {
            OSCommandHistory.printList();
        }
    }
    else if (keyword == "help")
    {
        std::cout << "To initiate operations, use the command line." << std::endl << "All Commands have a formatting like this:" <<std::endl << std::endl;
        std::cout << "Input? -> show time" << std::endl << std::endl;
        std::cout << "'show' is the keyword while time is what you want to know." << std::endl;
        std::cout << "Please consult the User Manual for a complete list of user commands available" << std::endl << std::endl;
    }
    return;
}

void OS::accessDirectory(std::string address)
{
    //Credit to http://www.cpp-home.com/tutorials/107_6.htm
    //Sets pointer for address so we can access opendir function
    char * charPointer = &address.at(0);
    struct dirent * entry;

    //Open Directory
    DIR* dir = opendir(charPointer);
    if (!dir)
    {
        std::cout << "Failure to Open Directory" << std::endl;
        return;
    }

    //Reading Directory and print listing
    std::cout << "Directory contents:" << std::endl;
    while ( (entry = readdir(dir)) != NULL)
    {
        std::cout << entry -> d_name << std::endl;
    }

    //Close directory
    if (closedir(dir) == -1)
    {
        std::cout << "Failure to closedir" << std::endl;
    }
    return;
}
