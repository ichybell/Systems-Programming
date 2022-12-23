#!/bin/bash  

# A simple bash script that counts the number of characters in a file
# Usage: ./read.sh -f FILE

#getopts is used with a custom flag to use arguments as variables for the file
while getopts f: flag
do
    case "${flag}" in
        f) file=${OPTARG};;
    esac
done

#If statement to check if user has used script correctly
if [ -z "$1" ]
  then
    echo "Usage: ./read.sh -f FILE"
    exit 0
fi

#Reading the file line by line
while read -r line; do          
STR=$line  
done < $file  

#Counts the number of characters in the file while excluding whitespace
no=$(echo $STR | tr -d '[:space:]' | wc -m)

echo "The number of characters in $file excluding whitespaces are $no"
