path=$1
echo -n "Number of Directories : "
find $path -type d -print | wc -l
echo -n "Number of Files : "
find $path -type f -print | wc -l
find $path -type f -perm +111 | awk 'BEGIN{FS="/"} {print $NF}'
