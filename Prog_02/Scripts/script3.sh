#!/bin/bash

#Prog02
#John Sullivan
#2/15/2020
#Part III: Directory Catalog in Bash
#Version 3

#This script will compile the .c file for assignment 02, after checking it exists
#Then, it will run the compilied program with the second input.
#The program will then wait for an input (a query) and respond with an answer. 

input=""
fileNames=""

if [ ! "$(ls -A "$2")" ]; 
then 
	echo "Directory for .dat files you provided is empty or doesn't exist."; 
fi
echo " ------------------------------- "
echo "| Reading files from directory..|"
echo " ------------------------------- "
if test -f "$1";
then
	cd "$2"
	
	#Loops over all .dat files in current directory. 
	for fName in "$(ls -A "$2")";
	do
		fileContents=`cat $fName`
		input=$input$fileContents" ";
	done
	
	#Goes back to the previous directory silently
	cd ~-
	gcc "$1" -o prog02
	echo " ---------------------------------- "
	echo "|Program started... Ready for query|"
	echo " ---------------------------------- "
	./prog02 $input;
else
	echo "The .c file you provided is empty or doesn't exist."; 
fi

