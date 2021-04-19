dwm - dynamic window manager
============================
dwm is an extremely fast, small, and dynamic window manager for X.

Patches
-------
+ dwmblocks patch
+ statuscmd
+ systray
+ attach aside 
+ attach below 
+ autostart
+ center
+ bar height
+ vanity gaps
+ gapless grid mode
+ scratchpads
+ pertag
+ pertag vanity gaps
+ swallow
+ steam patch 
+ cycle layouts
+ movestack

Requirements
------------
In order to build dwm you need the Xlib header files.


Installation
------------
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install


Running dwm
-----------
Add the following line to your .xinitrc to start dwm using startx:

    exec dwm



Configuration
-------------
The configuration of dwm is done by creating editing the config.def.h
and (re)compiling the source code with:

    make clean install
    
Libraries 
---------
Swallow needs the libx11 library
    sudo pacman -S libx11
   
