# Display configuration
xrandr --output DP-2 --primary --mode 1920x1080 --rate 144 --left-of DP-4 &
xrandr --output DP-4  --mode 1920x1080 --rate 144 --right-of DP-2 &

# Mouse
xinput --set-prop 9 298 -0.70 

# Status Bar
slstatus &

# Compositor 
picom &

# Wallpaper
nitrogen --restore 




