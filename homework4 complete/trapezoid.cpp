/*=============================================================
	COURSE:	CSC460, homework4
	PROGRAMMERS: 	Cameron Weston, Zach Olson (Grok ID: CW, ZO)
	MODIFIED BY: 	Cameron Weston, Zach Olson (Grok ID: CW, ZO)
	LAST MODIFIED DATE:	3/29/16
	DESCRIPTION:	Program to calculate area under a curve using trapezoidal sums.
                    Each child process is responsible for calculating one trapezoid
                    and returning its sub sum to the parent to calculate the over all
                    sum under the curve.
    CONTRIBUTIONS:
    Cameron Weston 50%
    -set up main with error checking
    -set up struct to keep track of child pid and area
    -created pipes for parent and children
    -checked if child completed computation and gave child another trapezoid
    -took results and child pids and displayed them

    Zach Olson 50%
    -set up calculations file to compute the area under the curve
    -set up make file
    -gave children trapezoids to compute
    -sent results to parent from child

	FILES:	trapezoid.cpp, datastruct.cpp, calculations.cpp, datastruct.h, makefile 
	IDE/COMPILER/INTERPRETER:	GNU g++
	INSTRUCTION FOR COMPILATION AND EXECUTION:
	1. type:	c++11   trapezoid.cpp, datastruct.cpp   -o   trapezoid
				c++11 calculations.cpp -o calculations
	or
	make	to COMPILE
	2. type:	./trapezoid 	to EXECUTE
=============================================================*/
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sstream>
#include <ctype.h>
#include <vector>
#include <iomanip>  //for precision
#include "datastruct.h"

using namespace std;

int main(int argc, char *argv[]){

        if(argc != 5) { //explains how to run the program
                cout << "Please execute program like this: ./trapezoid left right n m" << endl;
                cout << "left is the left bound, right is the right bound, n is the number of trapezoids, and m is the number of child processes to create." << endl;
                exit(0);
        }
        else if (atoi(argv[2]) <= atoi(argv[1])){ //If right <= left terminate
                cout << "right cannot be less than or equal to left!" << endl;
                cout << "Please enter an integer value for left and right" << endl;
                exit(0);
        }
        else if (atoi(argv[3]) <= 0){    //Checks if n is greater than 0
                cout << "N must be greater than 0" << endl;
                exit(0);
        }
        else if ((atoi(argv[4]) <= 0) || (atoi(argv[4]) > 8)){ //If not 0 < m <= 8 terminate
                cout << "M must be greater than 0 and less than or equal to 8" << endl;
                exit(0);
        }

        //DECLARE AND SAVE ALL VARIABLES WE WILL NEED
        int left = atoi(argv[1]);
        int right = atoi(argv[2]);
        int n = atoi(argv[3]);
        int m = atoi(argv[4]);

        double trapwidth = (right - left)/double(n);    //calculates base width of trapezoids
        double currentleft = double(left);              //current left bound of current trapezoid
        double currentright = double(left) + trapwidth; //current right bound of current trapezoid

//-----------------------------------------------------------------//

        //Set up Pipes for children to use
        int childToParent[2]; //Pipes subSum and pid back to parent program
        int parentToChild[2]; //Sends trapezoid info to child program to calculate subSum
        pid_t pid;
        int spawnNumber = min(n,m); //Gets minimum 'Spawn number' for child processes

        vector<vector<int>> childCounter;   //2D array to store how many trapezoids each child has calculated

        childCounter.resize(spawnNumber, vector<int>(3,0)); //Initializes all values to 0
        // [i][0] will store the child pid
        // [i][1] will store child pipe
        // [i][2] will store number of trapezoids calculated by that child

        if(pipe(childToParent) == -1){ //Initialize the 1 child to Parent pipe
            cout << "\n*** Failed: PARENT pipe(...) ***\n";
            exit(0);
        }

//**************************************************************************************//
//Create slave processes to handle the subsum trapezoid calculations
//**************************************************************************************//
    for (int i=0; i < spawnNumber; i++){
        //1. Create a pipe
        //ERROR CHECKING
        if (pipe(parentToChild) < 0){
            perror("\n*** Failed: child pipe ***\n");
            for(int i=0; i < childCounter.size(); i++){
                if(childCounter[i][0] != 0){
                    kill(childCounter[i][0], SIGKILL); //IF a pipe fails to open, terminate all child processes
                }
            }
            exit(0);
        }
        //2. Create a child
        //ERROR CHECKING FOR CHILD
        pid = fork(); //pid saves value AND calls fork call at the same time

        if (pid < 0){
            cout << "Fork Failed " << endl;
            for (int i=0; i <childCounter.size(); i++){
                if (childCounter[i][0] != 0){
                    kill (childCounter[i][0], SIGKILL); //IF a fork fails, terminate all child processes
                }
            }
            exit(0);
        }
        //**************************************************************************************//
        //CHILD
        //*************************************************************************************//
        else if (pid == 0){
            execl("calculations", "", to_string(childToParent[1]).c_str(), to_string(parentToChild[0]).c_str(), NULL);
            cout << "Error occured in execl(...)!\n" << endl;
        }
        //***********************************************************************************//
        //PARENT
        //**********************************************************************************//
		else{

				//3. Write to the child
				write(parentToChild[1], &currentleft, sizeof(double));//write current left to pipe
				write(parentToChild[1], &currentright, sizeof(double));//write current right to pipe

				childCounter[i][0] = pid; //stores child pid into array childCounter
				childCounter[i][1] = parentToChild[1]; //stores child pipe into array childCounter

				currentleft = currentright;
				currentright += trapwidth;

		}
    }
//*********************************************************************************//
//PROCESS CONTROL
//********************************************************************************//
		int remainingTraps = n - spawnNumber; //Remaining number of trapezoids after children are spawned
		int trapCounter = 0; //How many trapezoids have already been dealt with
		double integral = 0;
		Data *tempStruct = new Data;

		while(trapCounter != n){ //Calculates how many trapezoids each child has, find the area and stores it
				read(childToParent[0], tempStruct, sizeof(Data));
				integral += tempStruct->area;	//Increments the final answer by the subSum of each trapezoid
				trapCounter += 1;	//Counts number of trapezoids each child handles
				int i=0;	//Increments through the children and sees which ones need another trapezoid job
				bool finished = true;
				while (finished){

						if(tempStruct->pid == childCounter[i][0]){	//If returned child pid matches pid in array, assigns it a new job because its done
								finished = false;
								childCounter[i][2] += 1; //increase number of traps child calculated
								if (remainingTraps != 0){//if there are remaining trapezoids...
										write(childCounter[i][1], &currentleft, sizeof(double));//Sends another trapezoid through pipe to child
										write(childCounter[i][1], &currentright, sizeof(double));
										currentleft = currentright;
										currentright += trapwidth;
										remainingTraps--;
								}
						}
						i++; //increment i to look at next child
				}
		}

		close(childToParent[0]); //close pipe to parent read head
		close(childToParent[1]); //close pipe to parent write head
		for (int i=0; i < childCounter.size(); i++){

				cout << "Child" << i << " with pid " << childCounter[i][0] << " has calculated " <<
				childCounter[i][2] << " trapezoids" << endl;

				close(childCounter[i][1]); //close childToParent pipe
				close(childCounter[i][1]-1);
				kill(childCounter[i][0], SIGKILL); //terminate the child after everything is finished
		}

		cout << "The Integral is: " << setprecision (6) << fixed << integral << endl;
		return 0;

}
