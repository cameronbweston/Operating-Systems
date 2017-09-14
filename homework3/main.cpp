/*=============================================================
	COURSE:	CSC460, homework3
	PROGRAMMERS: 	Cameron Weston, Zach Olson (GROK ID: cw, zo)
	MODIFIED BY: 	Cameron Weston and Zach Olson
	LAST MODIFIED DATE:	3/17/16
	DESCRIPTION:	This program is to read words from a file using child processes and to
                    classify them by their types
	FILES:	main.cpp, classifier.cpp, makefile
	IDE/COMPILER/INTERPRETER:	GNU g++
	INSTRUCTION FOR COMPILATION AND EXECUTION:
	1. type:	c++11   xxx.cpp   -o   xxx
	or
	make	to COMPILE
	2. type:	./xxx	to EXECUTE
=============================================================*/
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include "textType.h"
using namespace std;

int main(int argc, char * argv[]){
    if (argc != 2){
        cout << "Please start the program like this: " << endl;
        cout << "./classifier [aFileName] " << endl;
        exit(0);
    }
        string fileName = argv[1];
        textType(fileName); //pass in file name and call function
    return 0;
}
