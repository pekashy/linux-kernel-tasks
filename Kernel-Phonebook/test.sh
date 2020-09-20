#!/bin/bash
make test
mkdir sub
cp test sub/init
cd sub
find . | cpio -o -H newc | gzip > ../test_fs.cpio.gz
cd ..
rm -rf sub
qemu-system-x86_64 -kernel linux-4.19.144/arch/x86_64/boot/bzImage -initrd test_fs.cpio.gz -m 512m
rm test_fs.cpio.gz