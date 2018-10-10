#!/bin/bash


export FREQ=1200000
export FREQ2=1596000

echo userspace > /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
echo "$FREQ" > /sys/devices/system/cpu/cpu0/cpufreq/scaling_min_freq
echo "$FREQ" > /sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq
echo "$FREQ" > /sys/devices/system/cpu/cpu0/cpufreq/scaling_setspeed

echo userspace > /sys/devices/system/cpu/cpu4/cpufreq/scaling_governor
echo "$FREQ2" > /sys/devices/system/cpu/cpu4/cpufreq/scaling_min_freq
echo "$FREQ2" > /sys/devices/system/cpu/cpu4/cpufreq/scaling_max_freq
echo "$FREQ2" > /sys/devices/system/cpu/cpu4/cpufreq/scaling_setspeed

/usr/bin/appcontroller /opt/toradex-and-xnor/bin/toradex-and-xnor
