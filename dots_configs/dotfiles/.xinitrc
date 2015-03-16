
#!/bin/bash

# hash fonts
xset +fp /usr/share/fonts/local
xset fp rehash

# disable blanking
xset s off &
xset -dpms &

# set the backdrop
xsetroot -solid "#777777" &
xsetroot -cursor_name left_ptr & 

hsetroot -fill /usr/share/backgrounds/zbthing.jpg &

# source the terminal colors
xrdb -merge ~/.Xresources &

# Ctrl-Alt-Backspace kills the X session
setxkbmap -option terminate:ctrl_alt_bksp &

KERNEL=$(uname -smr)
while true
do
   LOCALTIME=$( date '+%a %e %b %Y - %k:%M')
   WLAN="$(/sbin/iwconfig wlan0 | grep ESSID | sed 's/.*ESSID:"//g; s/"\s*$//g')   $(/sbin/iwconfig wlan0 | grep 'Link Quality' | sed 's/\s*Link Quality=//; s/\s.*//')"
   UPT="$(uptime -p)"
   TEMP="$(($(cat /sys/class/thermal/thermal_zone0/temp) / 1000))"
   BATT="$(cat /sys/class/power_supply/C1A6/capacity)"
   MEM="$( free -m | grep "cache:" | awk '{print $3 "mb"}' )"
   VOL=$(amixer get Master | tail -1 | sed 's/.*\[\([0-9]*%\)\].*/\1/')
   MUSIC="$(mocp -Q %state\ ""\ %artist\ "  "\ %song\ "  "\ %ct\ -\ %tt)"
if [ $marquis -eq "0" ];then
       xsetroot -name "$KERNEL >> $LOCALTIME  "
       marquis=1
   elif [ $marquis -eq "1" ]; then
       xsetroot -name "@  $SHELL >> $LOCALTIME  "
       marquis=2
   elif [ $marquis -eq "2" ]; then
       xsetroot -name "^  $WLAN >> $LOCALTIME  "
       marquis=3
   elif [ $marquis -eq "3" ]; then
       xsetroot -name "$UPT >> $LOCALTIME  "
        marquis=4
   elif [ $marquis -eq "4" ]; then
      xsetroot -name "t  $TEMP°c      b  $BATT%      r  $MEM      v  $VOL >> $LOCALTIME  "
       marquis=5
   elif [ $marquis -eq "5" ]; then
       xsetroot -name "$MUSIC >> $LOCALTIME  "
        marquis=0
   else
       xsetroot -name "$LOCALTIME  "
        marquis=0
fi
   sleep 5s
done &

exec /usr/local/bin/dwm
