#ifndef COMMANDLIST_H
#define COMMANDLIST_H

#include <vector>
#include <command.h>

class commandList
{
    public:
        commandList();
        ~commandList();
        bool addCommand(command newCommand);
        void printList();
    protected:
    private:
        std::vector<command> commandHistory;
        std::vector<std::string> validCommands;
};

#endif // COMMANDLIST_H
