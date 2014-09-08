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
        //Construct command
        command userCommand(newInput);

        OSCommandHistory.addCommand(userCommand);
        if (userCommand.returnValidCommand() == true)
        {
            executeOrder(userCommand);
        }
        else if (newInput == "exit")
        {
            //Confirms Exit
            std::cout << "Are you sure? We just started! Y/N" << std::endl;
            getline(std::cin,newInput);
            if (newInput == "Y" || newInput == "y")
            {
                break;
            }
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
        help();
    }
    else if (keyword == "set")
    {
        newCommand.convert(2);
        secondaryInformation = newCommand.returnTargetInformation();
        if (secondaryInformation == "date")
        {
            systemInfo.setDate();
        }
    }
    else
    {
        std::cout << "Invalid Command" << std::endl;
    }
    return;
}

void OS::accessDirectory(std::string address)
{
    //Credit to http://www.cpp-home.com/tutorials/107_6.htm
    //Sets pointer for address so we can access opendir function
    //This variable is for when you realize the text is going off the screen
    int printCounter = 1;
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
        //Allows user to see info, pause, and then move on to any extra information
        if (printCounter % 19 == 0)
        {
            pauseForUser();
        }
        std::cout << entry -> d_name << std::endl;
        printCounter++;
    }

    //Close directory
    if (closedir(dir) == -1)
    {
        std::cout << "Failure to closedir" << std::endl;
    }
    std::cout << std::endl;
    return;
}

//Prints available commands to the user
void OS::help()
{
    std::vector<std::string> currentCommands = OSCommandHistory.returnValidList();
    char currentCharacter = 'A';
    std::string dumby;

    //Prints list from valid commands and assigns a character to represent each one
    std::cout << std::endl << "This is a list of acceptable Commands; Press the character relating to that " << std::endl << "command to learn more about it. Type 'Q' to quit." << std::endl;
    for (unsigned int i = 0; i < currentCommands.size(); i++)
    {
        std::cout << currentCharacter << ". " << currentCommands.at(i) << std::endl;
        currentCharacter = currentCharacter++;
    }

    //Accepts Input from User
    std::cin >> currentCharacter;


    switch(currentCharacter)
    {
    case 'A':
    case 'a':
        std::cout << "The 'show' command helps you display different information about your Operating System:" << std::endl;
        std::cout << "show time - will display the current local time" << std::endl;
        std::cout << "show date - will display the current date" << std::endl;
        std::cout << "show version - will show the current version of the Operating System" << std::endl;
        break;
    case 'B':
    case 'b':
        std::cout << "The 'print' command allows you to print certain list" << std::endl;
        std::cout << "print previous commands - will display the previous commands inputted by the user" << std::endl;
        break;
    case 'C':
    case 'c':
        std::cout << "The 'set' command lets you input specific values for different items" << std::endl;
        std::cout << "set date - user sets the date" << std::endl;
    case 'Q':
    case 'q':
        break;
    default:
        std::cout << "That character is not a valid choice." << std::endl;
    }

    //Clears input buffer
    std::cin.ignore();

    return;
}



