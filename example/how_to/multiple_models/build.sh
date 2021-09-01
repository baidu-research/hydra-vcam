#!/bin/bash

echo -n "Please make sure you have backed up lib or bin(y or n)"
read Key
if [ $Key = "y" ];then
	rm -rf lib/ bin/
elif [ $Key = "n" ];then
	echo "n"
else
	echo "other"
fi

echo "copy lib/libvcam.a ...."
if [ ! -d "lib/" ];then
	mkdir lib/
	if [ ! -f "lib/libvcam.a" ];then
		cp ../../../sdk/source/library/Linux/C\&C++/libvcam.a lib/
	else
		echo "libvcam.a is exist"
	fi
else
	echo "lib/ is exist"
	if [ ! -f "lib/libvcam.a" ];then
		cp ../../../sdk/source/library/Linux/C\&C++/libvcam.a lib/
	else
		echo "libvcam.a is exist"
	fi
fi

echo "mkdir bin...."
if [ ! -d "bin/" ];then
	mkdir bin/
	echo "copy blob...."
	cp -r ../../../sdk/source/model/ bin/blob
	echo "copy moviUsbBoot...."
	cp ../../../sdk/source/library/Linux/C\&C++/moviUsbBoot bin/
	chmod +x bin/moviUsbBoot
	echo "copy fw....."
	cp -r ../../../sdk/source/firmware/fw/ bin/
else
	echo "bin/ is exist"
	echo "copy blob ......"
	if [ ! -d "bin/blob/" ];then
		cp -r ../../../sdk/source/model/ bin/blob
	else
		echo "bin/blob/ is exist"
	fi

	echo "copy moviUsbBoot...."
	if [ ! -f "bin/moviUsbBoot" ];then
		cp ../../../sdk/source/library/Linux/C\&C++/moviUsbBoot bin/
		chmod +x bin/moviUsbBoot	
	else
		echo "moviUsbBoot is exist"
	fi

	echo "copy fw ...... "
	if [ ! -d "bin/fw/" ];then
		cp -r ../../../sdk/source/firmware/fw/ bin/
	else
		echo "bin/fw/ is exist"
		echo "copy vcam.mvcmd"
		if [ ! -f "bin/fw/vcam.mvcmd" ];then
			cp ../../../sdk/source/firmware/fw/vcam.mvcmd bin/fw/
		else
			echo "vcam.mvcmd is exist"
		fi
	fi
fi
make
