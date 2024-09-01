#!/bin/sh

filesdir=$1
searchstr=$2

if [ $# -lt 2 ]
then
    echo "argument count is less than 2"
    exit 1
elif [ ! -d "$filesdir" ]
then
    echo "$1 is not a directory"
    exit 1
fi

file_count=$(find "$filesdir" -type f | wc -l)
line_count=$(grep -r "$searchstr" "$filesdir" | wc -l)

echo "The number of files are ${file_count} and the number of matching lines are ${line_count}"
