mem="$(free -h | awk '/^Mem:/ {print $3 "/" $2}')"
echo -e " $mem RAM "

