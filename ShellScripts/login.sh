#!/bin/bash

# A simple shell script that shows you how many times a user has logged onto system using only their UID

echo "Please input the UID you would like to use"
read UserID #Get the UID from the user as input
username=$(id -un -- $UserID) #Get the username associated with the UID
logontime=$(last $username | wc -l) #Get the number of times the user has logged onto the system by reading the /var/log/wmtp file 
echo "$username has logged on $logontime times"

