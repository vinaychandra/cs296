#!/bin/bash
if (( $1 == '1' ))
then
	tar czf ./src
fi

if (( $1 == '2' ))
then 
	cd ./src
	for file in *.cpp
	do
		gzip -c $file > $file".gz"
	done
	tar cvf src.tar *.gz
fi
