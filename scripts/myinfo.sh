#!/bin/bash

echo "Today is " $(date '+%A, %d %B, %Y')
current_year=$(date '+%Y')
ubuntu_name=$(echo $(cat /etc/lsb-release | sed -e 's/DISTRIB_CODENAME=\(.*\)/\1/' -e 's/DISTRIB_.*//'))
ubuntu_version=$(echo $(cat /etc/lsb-release | sed -e 's/DISTRIB_RELEASE=\(.*\)/\1/' -e 's/DISTRIB_.*//'))
kernel_version=$(uname -v)
ramkb=$(cat /proc/meminfo | head -n 1 | awk '{print $2}')
ram_use=$(cat /proc/meminfo | awk '{if(NR==2) print $2}')
ram_free=$(($ramkb - $ram_use))
disk_kb=$(df | awk '{if(NR==2) print $1}')
disk_use=$(df | awk '{if(NR==2) print $5}')
characters=$(echo -n $(cat ./scripts/myinfo.sh) | sed 's/ //g' | wc -m)
diff (){
	fulldate=$(date -d "$current_year-$2-$1 00:00:00" '+%F %T')
	seconds_left=$(( $(date -d"$fulldate" +%s) - $(date +%s)))
	if [ $seconds_left -le 0 ]; then
		fulldate=$(date -d "$(($current_year+1))-$2-$1 00:00:00" '+%F %T')
		seconds_left=$(( $(date -d"$fulldate" +%s) - $(date +%s)))
	fi
	weeks=$(($seconds_left/60/60/24/7))
	seconds_left=$(($seconds_left - $weeks*60*60*24*7))
	days=$(($seconds_left/60/60/24))
    seconds_left=$(($seconds_left - $days*60*60*24))
    hours=$(($seconds_left/60/60))
    seconds_left=$(($seconds_left - $hours*60*60))
    echo "There are $weeks weeks $days days and $hours hours left for the birthday of $3"
}

diff 21 12 "Sai Charan"
diff 21 6 "Vinay Chandra"
diff 5 5 "Nikhil Sri Ram"

up_time(){
	uptime | awk '{
		if($4 == "days,")print $3" "$4" "substr($5,0,length($5))" hours."	
		else if($4=="min,")print "0 days, 0:"$3" hours."
		else print "0 days, "substr($3,0,length($3))" hours."
	}'
}

echo "Thank you for asking, $USER"
echo "Your system has been running for $(up_time)"
echo "The current disk on which your home folder is located is $disk_kb and is $disk_use full"
echo "You are running $ubuntu_name and $ubuntu_version with Kernel $kernel_version"
echo "Your machine has "$(echo "scale=2;"$ramkb "/ 1048576" | bc)" GB RAM. Of which "$(echo "scale=2;"$ram_free "* 100 /" $ramkb | bc)"% is in use."
echo "This script has $(wc -w < ./scripts/myinfo.sh) words, $(wc -l < ./scripts/myinfo.sh) lines and $characters characters (without counting whitespace)"

