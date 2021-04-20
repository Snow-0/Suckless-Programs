#!/bin/sh

# Prints the current volume or 🔇 if muted.

case $BLOCK_BUTTON in
	1) setsid -f pavucontrol ;;
esac

[ $(pamixer --get-mute) = true ] && echo   && exit

vol="$(pamixer --get-volume)"

if [ "$vol" -gt "60" ]; then
	icon="墳  "
elif [ "$vol" -lt "20" ]; then
	icon="奄  "
else
	icon="奔  "
fi

echo "$icon$vol%"

