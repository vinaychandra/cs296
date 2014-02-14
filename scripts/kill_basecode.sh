#!/bin/bash

if ps aux | grep "[3]1_exe" > /dev/null
then
	echo "Basecode is Running"
	code_owner=$(ps aux | grep [_]31_exe | awk '{print $1}' | head -1) ;
	current_owner=$(ps aux | grep [k]ill_basecode | awk '{print $1}' | head -1);

	if (( code_owner==current_owner ))
	then
		echo "Do you want to kill the base process? "
		read option
		if [ "$option" == "y" ] || [ "$option" == "Y" ]
		then
			echo "Teminating... "
			pid=$(ps ax | grep [_]31_exe | awk '{print $1}' | head -1) ;
			kill $pid;
			echo "Terminated"
		else
		echo "Termination terminated"
		fi

	else
		echo "You do not have the permission to run terminate the process"
	fi
else
	echo "Basecode is Stopped"
fi
