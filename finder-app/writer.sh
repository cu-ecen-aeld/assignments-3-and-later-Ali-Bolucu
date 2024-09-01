#!/bin/sh

writefile=$1
writestr=$2

if [ $# -lt 2 ]
then
    echo "argument count is less than 2"
    exit 1
fi

# dirname: Extract directory part of a file name
if [ ! -d "$(dirname "$writefile")" ]
then
    mkdir -p "$(dirname "$writefile")"
fi

# in order to overwrite
if [ -f "$writefile" ]
then
    rm "$writefile"
fi

touch "$writefile"
echo ${writestr} >> $writefile
