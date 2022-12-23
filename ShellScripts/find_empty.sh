# A simple shell script that counts number of empty folders in a directory
# and outputs the list of those folders and time created

#!/bin/bash

#Store within a variable names of empty files and folders in a specific directory (with file size=0)
emptyfiles=$(du * | awk '$1 == 0 { print $2 }');

#Display the name and creation time of the empty files/folders
stat -c '%n %w' $emptyfiles

