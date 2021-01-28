#!/bin/bash
clear

# Variables formatting the script text red/green for visibility
PATH=/bin:/usr/bin:
NONE='\033[00m'
RED='\033[01;31m'
GREEN='\033[01;32m'

# Success of program
success=0

# Run this function when EXPECTING an error, due to a bad file
goodError()
{
	if [ $? -ne 0 ]
	then
		echo -e "${GREEN}\nCode threw an error for a bad test case. Yay!\n${NONE}"
	else
		echo -e "${RED}\nCode should've returned -1, but didn't. Boo.\n${NONE}"
		success=-1;
	fi
}

# Run this function if your code SHOULD NOT throw an error
badError()
{
	if [ $? -ne 0 ]
	then
		echo -e "${RED}\nCode should've run successfully, but didn't. Boo.\n${NONE}"
		success=-1;
	else
		echo -e "${GREEN}Code ran successfully on good input! Yay!\n${NONE}"
	fi
}

# Compile your code
printf "Compiling...\n"
make -C .. all

# Did the compilation work?
if [ $? -ne 0 ]
then
	echo "Didn't work!"
	echo -e "${RED}Could not compile code using your makefile. :(\n${NONE}"
	success=-1;
	exit
fi

# Check invalid files
for i in $( find *_invalid.txt ); do
	echo "Running pa2 on file '$i'..."
	../PA2 $i output.txt
	goodError
done

# Check valid files
for i in $( find *_valid.txt ); do
	echo "Running pa2 on file '$i'..."
	../PA2 $i output.txt
	badError
done

# We're done! Summarize
if [[ $success -eq 0 ]]
then
	echo -e "${GREEN}=========================================${NONE}"
	echo -e "${GREEN}Code handled all test cases successfully!${NONE}"
	echo -e "${GREEN}=========================================${NONE}"
else
	echo -e "${RED}========================${NONE}"
	echo -e "${RED}Code failed a test case!${NONE}"
	echo -e "${RED}========================${NONE}"
fi

# Remove all formatting of the console output we did above
tput sgr0
