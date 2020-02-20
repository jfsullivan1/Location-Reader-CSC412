#!/bin/bash

#Prog02
#John Sullivan
#2/15/2020
#Part III: Directory Catalog in Bash
#Version 2

#This script will print out all .dat files from a provided directory name. 

if [ ! "$(ls -A $"1")" ]; 
then 
	echo "Directory you provided is empty or doesn't exist."; 
else
	#found a similar method of my below line of code and made it my own at:
	#https://stackoverflow.com/questions/2437452/how-to-get-the-list-of-files-in-a-directory-in-a-shell-script
	find "$1" -maxdepth 1 -type f -name "*.dat" -printf "%f\n";
fi

