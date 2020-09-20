#!/bin/bash

shopt -s nullglob
for s in syscalls/*
do 
    echo "Found module $s"
    rm linux-4.19.144/${s}
    cp -r ${s} linux-4.19.144/
done

cp patch/root-Makefile linux-4.19.144/Makefile
cp patch/syscall_64.tbl linux-4.19.144/arch/x86/entry/syscalls/syscall_64.tbl
cp patch/syscalls.h linux-4.19.144/include/linux/syscalls.h