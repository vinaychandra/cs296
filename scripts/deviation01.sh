#!/bin/bash

iter_no=1
((no_reruns = 150))
((total_iter = 1500))

output_file=./data/average01.dat
input_file=./data/g31_lab05data_01.csv

rm -f $output_file
touch $output_file
chmod 666 $output_file


while (( iter_no <= total_iter ))
do
	echo -n $iter_no >> $output_file
	cat $input_file | sed -nr "s/^$iter_no,/&/p" | awk -vrer=$no_reruns -F "," '{sum1+=$3;sum2+=$4;sum3+=$5;sum4+=$6;sum5+=$7;sum6+=$3*$3;}END{printf " "sum1/rer" "sum2/rer" "sum3/rer" "sum4/rer" "sum5/rer" "sqrt((sum6/rer)-((sum1/rer)*(sum1/rer)))"\n"}' >> $output_file

	(( iter_no += 1 ))

done
