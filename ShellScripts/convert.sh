#!/bin/bash

# A bash script that converts all .bmp files in a given directory into .jpg files 
# It also outputs numbers of images converted
echo "Please input the file path for the file containing your .bmp files"
echo -e "\n\t\t**Use the fully defined path e.g. /home/kali**"
read input #Getting user input
myfiles=$(ls $input 2>/dev/null) #Listing all files and storing them in a variable

#Check to see if supplied directory is valid
if test -z "$myfiles"
then
    echo -e "\n\t\t**Please input a valid/existing directory**"
    exit 0
fi

#For loop getting all the files in the present directory
for file in $myfiles
do 
    if [ ${file} == *.bmp ]
    then 
        convert $file ${file}.jpg #Converting bmp file to jpeg file
        mv -- "${file}.jpg" "${file%.bmp}.jpg" #Changing file extension to jpg for converted file
    fi
done

#num variable used to count how many files have been modified
num=0

#For loop to get all files that have been converted 
for file in $myfiles
do
    if [ ${file} == *.jpg ]
    then
        num=`expr $num + 1`
    fi
done
echo -e "\nNo of files converted from bmp to jpg: $num \n\nCheck for files ending in .jpg to confirm"