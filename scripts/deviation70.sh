#!/bin/bash

iter_no=1
((no_reruns = 15)) # max_rand_elements
((iter_no = 70)) # use 70 in the final

output_file=./data/average70.dat
input_file=./data/g31_lab05data_02.csv

rm -f $output_file
touch $output_file
chmod 666 $output_file

echo -n $iter_no >> $output_file
cat $input_file | sed -nr "s/^$iter_no,/&/p" > $output_file
