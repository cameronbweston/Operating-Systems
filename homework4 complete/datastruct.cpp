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

struct Data{
        float area; //store area of each trapezoid
        int pid;    //store pid of each child/slave process
};
