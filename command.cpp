#include "command.h"

command::command(std::string input)
{
    //Constructor
    fullCommand = input;
    commandKeyword = "";
    targetInformation = "";
    validCommand = false;

    bool keywordComplete = false;

    //Travels through the given string
    for (unsigned int i = 0; i < fullCommand.size(); i++)
    {
        if (fullCommand.at(i) != '_' || fullCommand.at(i) != ' ')
        {
            //Acquires the Keyword
            if (keywordComplete == false)
            {
                //Looks for the first word
                while (fullCommand.at(i) != '_' && fullCommand.at(i) != ' ')
                {
                    //Builds a new string of the word
                    commandKeyword = commandKeyword + fullCommand.at(i);
                    i++;
                    if (i == fullCommand.size())
                    {
                        break;
                    }
                }
                keywordComplete = true;
            }
            //Acquires any extra information, if it exists
            else
            {
                //Looks for second word, if it exists
                while (fullCommand.at(i) != '_' && fullCommand.at(i) != ' ')
                {
                    //Builds a new string of the word
                    targetInformation = targetInformation + fullCommand.at(i);
                    i++;
                    if (i == fullCommand.size())
                    {
                        break;
                    }
                }
            }
        }



    }
    convert(1);
}

command::~command()
{
    //Destructor
}


void command::test()
{
    //test function for command object
    std::cout << "Whole Command: " << returnFullCommand() <<std::endl;
    std::cout << "Keyword: " << returnCommandKeyword() << std::endl;
    std::cout << "Target Information: " << returnTargetInformation() << std::endl;
    return;
}


//This function converts the new string into a format that is better recognized by the computer
void command::convert(int code)
{
    if (code == 1)
    {
        for (unsigned int i = 0; i < commandKeyword.size(); i++)
        {
            //Goes through and converts each letter to it's lower case value
            switch (commandKeyword.at(i))
            {
                case 'A':
                commandKeyword.at(i) = 'a';
                break;
                case 'B':
                commandKeyword.at(i) = 'b';
                break;
                case 'C':
                commandKeyword.at(i) = 'c';
                break;
                case 'D':
                commandKeyword.at(i) = 'd';
                break;
                case 'E':
                commandKeyword.at(i) = 'e';
                break;
                case 'F':
                commandKeyword.at(i) = 'f';
                break;
                case 'G':
                commandKeyword.at(i) = 'g';
                break;
                case 'H':
                commandKeyword.at(i) = 'h';
                break;
                case 'I':
                commandKeyword.at(i) = 'i';
                break;
                case 'J':
                commandKeyword.at(i) = 'j';
                break;
                case 'K':
                commandKeyword.at(i) = 'k';
                break;
                case 'L':
                commandKeyword.at(i) = 'l';
                break;
                case 'M':
                commandKeyword.at(i) = 'm';
                break;
                case 'N':
                commandKeyword.at(i) = 'n';
                break;
                case 'O':
                commandKeyword.at(i) = 'o';
                break;
                case 'P':
                commandKeyword.at(i) = 'p';
                break;
                case 'Q':
                commandKeyword.at(i) = 'q';
                break;
                case 'R':
                commandKeyword.at(i) = 'r';
                break;
                case 'S':
                commandKeyword.at(i) = 's';
                break;
                case 'T':
                commandKeyword.at(i) = 't';
                break;
                case 'U':
                commandKeyword.at(i) = 'u';
                break;
                case 'V':
                commandKeyword.at(i) = 'v';
                break;
                case 'W':
                commandKeyword.at(i) = 'w';
                break;
                case 'X':
                commandKeyword.at(i) = 'x';
                break;
                case 'Y':
                commandKeyword.at(i) = 'y';
                break;
                case 'Z':
                commandKeyword.at(i) = 'z';
                break;

                default:
                break;
            }
        }
    }
    else if (code == 2)
    {
        for (unsigned int i = 0; i < targetInformation.size(); i++)
        {
            //Goes through and converts each letter to it's lower case value
            switch (targetInformation.at(i))
            {
                case 'A':
                targetInformation.at(i) = 'a';
                break;
                case 'B':
                targetInformation.at(i) = 'b';
                break;
                case 'C':
                targetInformation.at(i) = 'c';
                break;
                case 'D':
                targetInformation.at(i) = 'd';
                break;
                case 'E':
                targetInformation.at(i) = 'e';
                break;
                case 'F':
                targetInformation.at(i) = 'f';
                break;
                case 'G':
                targetInformation.at(i) = 'g';
                break;
                case 'H':
                targetInformation.at(i) = 'h';
                break;
                case 'I':
                targetInformation.at(i) = 'i';
                break;
                case 'J':
                targetInformation.at(i) = 'j';
                break;
                case 'K':
                targetInformation.at(i) = 'k';
                break;
                case 'L':
                targetInformation.at(i) = 'l';
                break;
                case 'M':
                targetInformation.at(i) = 'm';
                break;
                case 'N':
                targetInformation.at(i) = 'n';
                break;
                case 'O':
                targetInformation.at(i) = 'o';
                break;
                case 'P':
                targetInformation.at(i) = 'p';
                break;
                case 'Q':
                targetInformation.at(i) = 'q';
                break;
                case 'R':
                targetInformation.at(i) = 'r';
                break;
                case 'S':
                targetInformation.at(i) = 's';
                break;
                case 'T':
                targetInformation.at(i) = 't';
                break;
                case 'U':
                targetInformation.at(i) = 'u';
                break;
                case 'V':
                targetInformation.at(i) = 'v';
                break;
                case 'W':
                targetInformation.at(i) = 'w';
                break;
                case 'X':
                targetInformation.at(i) = 'x';
                break;
                case 'Y':
                targetInformation.at(i) = 'y';
                break;
                case 'Z':
                targetInformation.at(i) = 'z';
                break;

                default:
                break;
            }
        }
    }
    return;
}

//Returns the Full Command String
std::string command::returnFullCommand()
{
    return fullCommand;
}

//Returns the Command Keyword
std::string command::returnCommandKeyword()
{
    return commandKeyword;
}

//Returns the Secondary Information
std::string command::returnTargetInformation()
{
    return targetInformation;
}

//Returns the boolean statement of whether it's a a valid command or not
bool command::returnValidCommand()
{
    return validCommand;
}

//Checks to see if it s a valid command
void command::checkValid(std::vector<std::string> validCommandList)
{
    //Checks through the list to see if this is a valid command on record
    for (unsigned int i = 0; i < validCommandList.size(); i++)
    {
        if (commandKeyword == validCommandList.at(i))
        {
            //Sets it to be a valid command
            validCommand = true;
        }
    }

    return;
}




//Command List functions

commandList::commandList()
{
    //Constructor
    constructValidList();
}

commandList::~commandList()
{
    //dtor
}

//Hard-Coding in valid commands
void commandList::constructValidList()
{
    //OS Request Commands
    validCommands.push_back("show");
    validCommands.push_back("print");
    validCommands.push_back("help");
    return;
}


//Adds command to list of previous commands
bool commandList::addCommand(command &newCommand)
{
    newCommand.checkValid(validCommands);
    if (newCommand.returnValidCommand() == true)
    {
        commandHistory.push_back(newCommand);
        return true;
    }
    else
    {
        return false;
    }
}


//Prints the list of accepted commands
void commandList::printList()
{
    std::cout << "Previous Commands: " << std::endl;
    for (unsigned int i = 0; i < commandHistory.size(); i++)
    {
        command currentCommand = commandHistory.at(i);
        std::cout << i+1 << ". " << currentCommand.returnCommandKeyword() << " " << currentCommand.returnTargetInformation() << std::endl;
    }
    std::cout << std::endl;
}
