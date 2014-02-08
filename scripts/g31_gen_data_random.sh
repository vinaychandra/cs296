#!/bin/bash
input=./data/g31_lab05data_02.csv
output=./data/g31_lab05data_random.csv

max_rand_elements=4
number_of_reruns=10
number_of_iters=50
current_iter=1

rm -f $output
touch $output

while (( current_iter <= number_of_iters ))
do
	for i in $(shuf -n $max_rand_elements -i 1-$number_of_reruns) 
	do
		sed -n $((($number_of_reruns*$current_iter-1)+$i))'p' < $input >> $output
	done
	(( current_iter += 1 ))
done
