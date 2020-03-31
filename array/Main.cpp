// array.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "array.h"


#define CONCAT(a, b) a ## b

int main()
{
    int ab = 15;

    std::cout << CONCAT(a, b) << std::endl;



    /*
    array<bool> boolArr(5);
    boolArr.push_back(1);
    boolArr.push_back(0);
    boolArr.push_back(1);
    boolArr.push_back(1);
    boolArr.push_back(1);
    boolArr.push_back(1);
    boolArr.push_back(1);
    boolArr.push_back(1);
    // array is full
    

    // boolArr.push_back(1);

    // std::cout << boolArr.size() << "\n" << boolArr[0] << std::endl;
    printByte(boolArr[0]);

    */

    /*
    byte a = 0x07;
    printByte(a);
    std::cout << std::endl;

    dropNthBit(a, 0);
    dropNthBit(a, 2);
    printByte(a);
    std::cout << std::endl;

    setNthBit(a, 7);
    printByte(a);
    std::cout << std::endl;

    std::cout << getNthBit(a, 7) << " " << getNthBit(a, 6);
    std::cout << std::endl;


    byte b = 0;
    printByte(b);
    */

}
