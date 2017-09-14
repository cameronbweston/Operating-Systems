/*=======================================================================
COURSE:                 CSC460, Homework #1
PROGRAMMERS:            Cameron Weston, Zach Olson
userID:                 CW (Cameron Weston), ZO (Zach Olson)
MODIFIED BY:
LAST MODIFIED DATE:
DESCRIPTION:
FILES:
IDE/COMPILER/INTERPRETER:   GNU g++
INSTRUCTION FOR COMPILATION AND EXECUTION:
    1. type:    c++11 xxx.cpp -o xxx
        or
            make    to COMPILE
    2. type: ./xxx  to EXECUTE
=========================================================================
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h> //for rand()
//#include "trapezoid.h"

using namespace std;

int main(int argc, char *argv[]){
    //Take in A and B
    //Left must be BIGGER than Right
    //Check for valid command line arguments ARGC == 3!!!

    if (argc != 3){
        cout << "Please execute the program like this: " << endl;
        cout << "./trapezoid left right" << endl;
        exit(0);
    }

    int left = atoi(argv[1]);
    int right = atoi(argv[2]);

    if (right <= left){
        cout << "The Right value must be greater than the Left value!" << endl;
        cout << "Please execute the program like this: " << endl;
        cout << "./trapezoid left right" << endl;
        exit(0);
    }
    else

    float finalAnswer;
    int n = rand() % 100 + 5;

    //finalAnswer = trapezoid(left, right, n);

return 0;
}
