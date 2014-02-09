#!/bin/bash
((iter_no = 1))
((rerun_no = 1))
((no_reruns = 150))
((total_iter = 1500))

while (( iter_no <= total_iter ))
do
#	echo $iter_no
	((rerun_no = 1))
	while (( rerun_no <= no_reruns ))
	do
		./mybins/cs296_31_exe $iter_no > ./data/g31out-$iter_no-$rerun_no.txt
		(( rerun_no += 1 ))
	done
	(( iter_no += 1 ))
done

