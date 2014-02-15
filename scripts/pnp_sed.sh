#!/bin/bash

input_file=data/pnp_austen.txt
output_file=data/pnp_austen_cs296.txt
#Elizabeth=Saicharan
#Lady Catherine=VinayChandra
#Darcy=Nikhil
sed "s/''/@/g" <$input_file >$output_file
sed -i 's/``/@/g' $output_file 
sed -i 's/@/"/g' $output_file
sed -i 's/Elizabeth/Saicharan/g' $output_file
sed -i 's/Lady Catherine/Vinay Chandra/g' $output_file
sed -i 's/Darcy/Nikhil/g' $output_file
