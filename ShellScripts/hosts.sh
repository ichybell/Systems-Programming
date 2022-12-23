# A simple script that scans IP addresses in a /24 subnet to find which IP's are up and running.

#!/bin/bash

echo -e "Welcome to the simple script that will scan all IP addresses in a given range with the assumption that the subnet mask is /24\n\n"
echo -e "Please provide the IP address you would like scanned while leaving out the last octet \n\ne.g. if IP=10.10.10.10, then input will be 10.10.10"
read IP

#Function to check if host is up using ping
host_is_up()
{
  ping -c 2 $1 > /dev/null
  [ $? -eq 0 ] echo IP: $i is up
}

#for loop to run through IP addresses and check if each of them is up
for i in $IP.{1..255} 
do
host_is_up $i & disown
done
