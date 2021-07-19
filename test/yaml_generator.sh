#!/bin/bash

echo "- [10, 23, 5, 11, 7]" > $1
len=$2
echo $2
for (( i=0; i<$len; ++i ))
do
    echo "-" >> $1
    bridge_len=$((RANDOM%100+1))
    echo " - $bridge_len" >> $1
    n=$((RANDOM%20+1))
    first_member=$((RANDOM%10+1))
    team_str="- [$first_member"
    for (( j=0; j<$n; ++j))
    do
	s=$((RANDOM%10+1))
	team_str="$team_str,$s"
    done
    echo "$team_str]" >> $1
done
