#!/bin/bash
rm -rf initrd
mkdir initrd
cd initrd
mkinitcpio -A base udev -g initrd.img
lsinitcpio -x initrd.img
rm initrd.img
cd ..
make test_loadable
chmod +x test_loadable
cp test_loadable initrd/
cd loadable 
make
cd ..
cp loadable/testmodule.ko initrd/
cp tli.sh initrd/
cd initrd
find . | cpio -o -H newc | gzip > ../test_fs.cpio.gz
cd ..
qemu-system-x86_64 -kernel linux-4.19.144/arch/x86_64/boot/bzImage -initrd test_fs.cpio.gz -m 512m
rm test_fs.cpio.gz