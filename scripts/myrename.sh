#!/bin/bash
cd ./src/
if (( $1 == '1' ))
then
	for files in *.cpp
	do
		mv $files $files".bak"
	done
fi
if (( $1 == '2' ))
then
	ls *.cpp | xargs -Ifiles mv files files.bak
#Another command that can be used is
# ls *.cpp | awk 'system { "mv " $0 $0".bak"}'
fi
