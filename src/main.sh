#!/bin/sh

#print kernel error default
echo 4 > /proc/sys/kernel/printk

#start ftp server, dir=root r/w, -t 600s(timeout)
#/usr/bin/tcpsvd 0 21 ftpd -w / -t 600 &

echo "Starting telnetd..."
/usr/sbin/telnetd &

#start syslogd & klogd, log rotated 3 files(200KB) to /var/log/messages
#syslogd -D -n -O /var/log/messages -s 200 -b 3 & # -l prio
#klogd -n & # -c prio

## set min free reserve KB
echo 256 > /proc/sys/vm/min_free_kbytes

#load basic driver
#insmod /usr/modules/ak_adc_key.ko
insmod /usr/modules/ak_rtc.ko
hwclock -s

#insmod /usr/modules/ak_fb.ko lcd_ctl_force_init=1
#insmod /usr/modules/ak_pwm_char.ko
#insmod /usr/modules/ak_fb.ko
#insmod /usr/modules/ak_saradc.ko
insmod /usr/modules/ak_i2c.ko
insmod /usr/modules/ak_pcm.ko
insmod /usr/modules/ak_gpio_keys.ko
#insmod /usr/modules/ak_gui.ko
insmod /usr/modules/ak_ion.ko
insmod /usr/modules/ak_leds.ko
#insmod led modules will reset gpio pin, so reset the led_gpio pin
echo 1 > /sys/class/leds/red_led/brightness
#insmod /lib/modules/4.4.192V2.1/kernel/drivers/mmc/core/mmc_core.ko
#insmod /lib/modules/4.4.192V2.1/kernel/drivers/mmc/card/mmc_block.ko
insmod /usr/modules/ak_mci.ko sdio_clk_mode=1
insmod /usr/modules/ak_uio.ko
insmod /usr/modules/exfat.ko
insmod /usr/modules/ak_motor.ko

#open adc
insmod /usr/modules/ak_saradc.ko

#load wifi module
/usr/sbin/wifi_init.sh &

#load sensor module
/usr/sbin/sensor_module_load.sh &

echo "Mounting sd card..."
sdDir="/etc/config/repairSdCard"
if test -e /dev/mmcblk0p1 ;then
	if [ -d "$sdDir" ]; then
		count=0
		while [ $count -lt 2 ]; do
			fsck.fat /dev/mmcblk0p1 -a
			status=$?
			echo "fsck.fat status = ${status}"
			if [ $status -eq 0 ]; then
				break
			else
				count=$((count+1))
			fi
		done
		rm -r "$sdDir"
		echo "$sdDir deleted"
	fi
	mount -rw /dev/mmcblk0p1 /mnt
elif test -e /dev/mmcblk0 ;then
	if [ -d "$sdDir" ]; then
		num=0
		while [ $count -lt 2 ]; do
			fsck.fat /dev/mmcblk0 -a
			ret=$?
			echo "fsck.fat ret = ${ret}"
			if [ $ret -eq 0 ]; then
				break
			else
				num=$((num+1))
			fi
		done
		rm -r "$sdDir"
		echo "$sdDir deleted"
	fi
	mount -rw /dev/mmcblk0 /mnt
fi

if test -d /mnt/agingtest ;then
	/usr/sbin/red_led.sh off
	/usr/sbin/blue_led.sh on
	cp /mnt/agingtest/aging_test /tmp/
	chmod 755 /tmp/aging_test
	/tmp/aging_test
	echo "start aging test."
else
	echo "*********************"
	echo "**** start ipcd *****"
	echo "*********************"
	/usr/bin/ipcd &
fi
