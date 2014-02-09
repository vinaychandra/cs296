#!/bin/bash
((iter_no = 1))
((rerun_no = 1))
((no_reruns = 150))
((total_iter = 1500))

output_file=./data/g31_lab05data_01.csv

rm -f $output_file
touch $output_file
chmod 666 $output_file

while (( iter_no <= total_iter ))
do
#	echo $iter_no
	((rerun_no = 1))
	while (( rerun_no <= no_reruns ))
	do
		file_name=./data/g31out-$iter_no-$rerun_no.txt
		echo -n "$iter_no,$rerun_no," >> $output_file
		cat $file_name | sed 's/[A-Za-z: ]*\([0-9.][0-9.]*\)[A-Za-z ]*/\1/' | grep [0-9][0-9]*[.][0-9][0-9]* | awk '{print}' ORS=',' >> $output_file
		echo "" >> $output_file
		(( rerun_no += 1 ))
	done
	(( iter_no += 1 ))
done

