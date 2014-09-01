#include "personalFunctions.h"


std::string convertIntToString(int number)
{
    std::string result = "";
    std::ostringstream exchange;
    exchange << number;
    result = exchange.str();
    return result;
}

