# Kernel Address&Phones book

linux-4.19.144 kernel is to be used. Tested on Manjaro 20.1 x64.

## Usage
1. On first run execute `./download.sh` - that will download and unzip kernel.
2. Execute `./build_kernel.sh` - that will build the kernel.
3. To test, run `./test_loadable.sh`, that will run load qemu emulator with the right kernel and loaded test executable. (`qemu` and `cpio` must be installed).
4. In qemu run `sh t`, `t` is a script, which loads kernel module and runs tests.
