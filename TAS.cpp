#pragma once
#include "includes.h"

int main()
{
    Citys city;
    while (1)
    {
        printf("Enter number to select function:\n");
        printf("1.addCityByNumber\n"
            "2.addCity\n"
            "3.reviseCityName\n"
            "4.eraseCity\n"
            "5.addPath\n"
            "6.revisePath\n"
            "7.erasePath\n"
            "8.findCheapestPath\n"
            "-1.esc\n");
        int opCode; cin >> opCode;
        switch (opCode)
        {
        case 1:
            city.addCityByNumber();
            break;
        case 2:
            city.addCity();
            break;
        case 3:
            city.reviseCityName();
            break;
        case 4:
            city.eraseCity();
            break;
        case 5:
            city.addPath();
            break;
        case 6:
            city.revisePath();
            break;
        case 7:
            city.erasePath();
            break;
        case 8:
            city.findCheapestPath();
            break;
        case -1:
            return 0;

        default:
            break;
        }
    }

    return 0;
}