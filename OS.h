#ifndef OS_H
#define OS_H

#include "command.h"
#include "OSInfo.h"
#include "PCB.h"
#include "processScheduler.h"
#include "memoryManager.h"

class OS
{
    public:
        OS();
        ~OS();
        void execute();

    protected:
    private:
        commandList OSCommandHistory;
        OSInfo systemInfo;
        processScheduler systemProcesses;

        void bluescreen();
        void startScreen();
        void executeOrder(command newCommand);
        void accessDirectory(std::string address);
        void help();
};

#endif // OS_H
