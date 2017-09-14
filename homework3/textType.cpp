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
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <fstream>
#include <ctype.h>
using namespace std;

//Read words from file located in tmp folder on grok//
vector<string> wordlist;    //Vector to store all words in file

int textType(string fileName){
    ifstream myfile;
    myfile.open("/tmp/" + fileName);
    if(!myfile.is_open())
    {
        cout << "Could not open file!" << endl;
    }
    string word;
    while(myfile >> word)
    {
        wordlist.push_back(word);
        cout << word << endl;
    }
    myfile.close();
//-------------------------------------------------//

for (int i=0; i < wordlist.size(); i++){
    string testResult = "string";
    string currentword = wordlist.at(i);

//1. Create a child
    int returnValue = fork();
    cout << "Parent process id: " << getppid() << endl;
//2. Error checking
    if(returnValue == -1){
        cout << "Child process failed" << endl;
        exit(0);
    }
    else if (returnValue == 0){
                cout << "Child creation number: " << i << endl;
                cout << "Child process id: " << getpid() << endl;
                cout << "Child assigned word: " << currentword << endl;

                //Checks
                for(int i = 0; i < currentword.length(); i++)
                {
                    if(!isdigit(currentword[i]))
                    {
                        if(currentword[i] == '.')
                        {
                            testResult = "float";
                            break;
                        }
                        else if (currentword[i] != '.')
                        {
                            testResult = "string";
                            break;
                        }
                        else
                        {
                            continue;
                        }
                    }
                    else
                    {
                        testResult = "integer";
                    }

                }

                cout << "Test result: " << testResult << endl;
                cout << endl;
                return 0;
            }
}
    return 0;
}
