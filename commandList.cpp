#include "commandList.h"

commandList::commandList()
{
    //ctor
}

commandList::~commandList()
{
    //dtor
}

//Adds command to list of previous commands
bool commandList::addCommand(command newCommand)
{
    commandHistory.push_back(newCommand);
}

//
void commandList::printList()
{
    std::cout << "Previous Commands: " << std::endl;
    for (unsigned int i = 0; i < commandHistory.size(); i++)
    {
        command currentCommand = commandHistory.at(i);
        std::cout << currentCommand.returnCommandKeyword() << " " << currentCommand.returnTargetInformation() << std::endl;
    }
}
