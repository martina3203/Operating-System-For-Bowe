#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <iostream>
#include <vector>

class command
{
    public:
        command(std::string input);
        virtual ~command();
        void test();
        std::string returnFullCommand();
        std::string returnCommandKeyword();
        std::string returnTargetInformation();
        void checkValid(std::vector<std::string> validCommandList);
        bool returnValidCommand();
        void convert(int code);
    protected:
    private:
        //This holds the full command as typed by the user
        std::string fullCommand;
        //This holds the word that is a command to the operating system
        std::string commandKeyword;
        //This is the secondary information added to the command
        std::string targetInformation;
        //Converts function to a usable command format
        bool validCommand;
};

class commandList
{
    public:
        commandList();
        ~commandList();
        bool addCommand(command &newCommand);
        void printList();
        std::vector<std::string> returnValidList();
    protected:
    private:
        std::vector<command> commandHistory;
        void constructValidList();
        std::vector<std::string> validCommands;
};


#endif // COMMAND_H
