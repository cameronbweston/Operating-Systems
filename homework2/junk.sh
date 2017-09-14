#!/bin/bash

#COURSE:         CSC460, HOMEWORK#2
#PROGRAMMERS:    Cameron Weston, Zach Olson
#MODIFIED BY:    Cameron Weston, Zach Olson
#LAST MODIFIED DATE: 2/16/16
#DESCRIPTION:        A BASH script that simulates the use of the recycle bin
#FILES:             junk 
#INSTRUCTION FOR COMPILATION AND EXECUTION:
#    1.type: chmod u+x junk  to MAKE EXECUTABLE
#    2.type: ./junk          to EXECUTE

if [ "$#" -eq 0 ]
	 then
    echo
    echo "This script simulates the use of a recycle bin and you can use the command like this:"
    echo "junk [-l\-p] [fileName1 fileName2 ...]"
    echo
    echo  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    echo
    echo "Enter junk -l [fileName1 fileName2 ...]"
    echo
    echo "Displays the current contents of the directory ~/RecycleBin, if it exists;"
    echo "otherwise, it will display \"Directory RecycleBin does not exist.\" "
    echo
    echo ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    echo
    echo "Enter junk -p [fileName1 fileName2 ...]"
    echo
    echo "Deletes all the content of the directory ~/RecycleBin if it exists, otherwise,"
    echo "it will display a message \"Directory RecycleBin does not exist.\" "
    echo
    echo ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    echo
    echo "Enter junk fileName1 fileName2 ..."
    echo
    echo "If ~/RecycleBin exists and it is a directory, the script checks each file in the file name list: if a"
    echo "file exists, the script moves it (with all its contents if it is a directory) from its current place"
    echo "to the RecycleBin."
    echo
    echo "If a file does not exist, the script displays an appropriate error message with the file name."

    echo "If ~/RecycleBin does not exist, the script creates the directory first, then moves the files as"
    echo "described above."
    echo
    echo "If ~/RecycleBin exists but it is not a directory, the script displays that there is an error."
    echo

elif [ $1 == "-l" ]                                     #Checks to see if the first argument is -l
	then
	if [ ! -d ~/RecycleBin ]                            #If the directory does not exist. Display error message
        then
        echo "Directory RecycleBin does not exist."
    else                                                #Otherwise, print out the path along with the contents inside the dir
        find ~/RecycleBin -type d -print
        ls ~/RecycleBin
    fi

elif [ $1 == "-p" ]                                     #Checks to see if the first argument is -p
    then
    if [ ! -d ~/RecycleBin ]                            #If the directory does not exist. Display error message
        then
        echo "Directory RecycleBin does not exist."
    else                                                #Otherwise, remove all of the contents inside RecycleBin
        find ~/RecycleBin
        rm ~/RecycleBin/*
    fi
else
    if [ -d ~/RecycleBin ]                              #CASE 1 Moves contents to RecycleBin
        then
        for arg in "$@"                                 #For every argument...
        do
            if [ -f $arg ]                              #If the file exists, move to RecycleBin
            then
                mv $arg ~/RecycleBin
            elif [ -d $arg ]                            #If directory exists, move it along with contents to RecycleBin
            then
                mv $arg ~/RecycleBin
            else                                        #If it does not exist, displays appropriate message
                echo $arg "does not exist"
            fi
        done
    elif [ ! -d ~/RecycleBin ]                          #CASE 2 If the directory does not exist...
        then
            if [ -f ~/RecycleBin ]                      #CASE 3 If RecycleBin is not a directory
                then
                    echo "RecycleBin exists but it is NOT a directory."     #Display Error Message

            else
            mkdir ~/RecycleBin                          #Creates the RecycleBin at the root
            for arg in "$@"                             #For every argument
            do
                if [ -f $arg ]                          #If it is a file, move to RecycleBin
                then
                    mv $arg ~/RecycleBin
                elif [ -d $arg ]                        #If it is a directory, move to RecycleBin with contents
                then
                    mv $arg ~/RecycleBin
                else                                    #if it does not exist, display error message
                    echo $arg "does not exist"
                fi
            done
            fi

    fi
fi

