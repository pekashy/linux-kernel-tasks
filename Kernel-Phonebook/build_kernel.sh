#!/bin/bash

shopt -s nullglob
cd syscalls
for s in *
do 
    echo "Found module $s"
    rm -r ../linux-4.19.144/${s}
    cp -r ${s} ../linux-4.19.144/
done

cd ..

cp patch/root-Makefile linux-4.19.144/Makefile
cp patch/syscall_64.tbl linux-4.19.144/arch/x86/entry/syscalls/syscall_64.tbl
cp patch/syscalls.h linux-4.19.144/include/linux/syscalls.h

cd linux-4.19.144
sudo make menuconfig
sudo make -j8
