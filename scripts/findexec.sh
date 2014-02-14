path=$1
find $path -type d -print | wc -l
find $path -perm +111
