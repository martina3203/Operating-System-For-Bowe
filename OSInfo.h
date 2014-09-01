#ifndef OSINFO_H
#define OSINFO_H

#include <command.h>
#include <Windows.h>
#include <ctime>
#include <sstream>
#include <personalFunctions.h>


class OSInfo
{
    public:
        OSInfo();
        virtual ~OSInfo();
        std::string returnOSName();
        float returnVersionNumber();
        std::string returnOSInfo(command request);
        void test();
    protected:
    private:
        void calculateTime();
        std::string time;
        std::string date;
        float versionNumber;
        std::string OSName;

};

#endif // OSINFO_H
