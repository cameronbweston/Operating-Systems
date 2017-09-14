/*=============================================================
	COURSE:	CSC460, homework4
	PROGRAMMERS: 	Cameron Weston, Zach Olson (Grok ID: CW, ZO)
	MODIFIED BY: 	Cameron Weston, Zach Olson (Grok ID: CW, ZO)
	LAST MODIFIED DATE:	3/31/16
	DESCRIPTION:	Program to calculate area under a curve using trapezoidal sums.
                    Each child process is responsible for calculating one trapezoid
                    and returning its sub sum to the parent to calculate the over all
                    sum under the curve.
    CONTRIBUTIONS:
	FILES:	xxx.cpp, makefile, 
	IDE/COMPILER/INTERPRETER:	GNU g++
	INSTRUCTION FOR COMPILATION AND EXECUTION:
	1. type:	c++11   xxx.cpp   -o   xxx
	or
	make	to COMPILE
	2. type:	./xxx	to EXECUTE
=============================================================*/
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sstream>
#include <ctype.h>
#include <math.h>
#include "datastruct.h"

using namespace std;

int main(int argc, char* argv[]){

    while (true) {
        double currentleft, currentright, trapwidth;

        read(atoi(argv[2]), &currentleft, sizeof(double)); //get current leftside from pipe
        read(atoi(argv[2]), &currentright, sizeof(double));//get current rightside from pipe

        trapwidth = currentright - currentleft; //calculate width of trapezoid base

        //Calculates Trapezoid Area by putting A and B into integral function
        double leftValue = (pow(currentleft, 2.0) + (2 * currentleft) + 4); //put A into function
        double rightValue = (pow(currentright, 2.0) + (2 * currentright) + 4); //put B into function
        double subSum = (((leftValue + rightValue)/2) * trapwidth); //calculate subSum of this trapezoid

        Data *dataholder = new Data;    //Create new struct object
        dataholder->pid = getpid();     //store pid of this child
        dataholder->area = subSum;      //store this trapezoid area in struct

        write(atoi(argv[1]), dataholder, sizeof(dataholder));   //Pipe this info to the other side
    }
    return 0;
}
