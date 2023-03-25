#!/bin/sh
set -xe

[ $(id -u) != 0 ] && echo must be run as root && exit 1
cp test-logger-mod.ko /usr/lib/modules/`uname -r`/kernel/drivers
rmmod test_logger_mod || /bin/true
modprobe test_logger_mod
depmod
