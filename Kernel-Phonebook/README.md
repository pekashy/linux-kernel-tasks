# Kernel Address&Phones book

linux-4.19.144 kernel is to be used. Tested on Manjaro 20.1 x64.

## Usage
1. On first run execute `./download.sh` - that will download and unzip the right kernel.
2. Execute `./build_kernel.sh` - that will build kernel with our custom modules.
3. To test, run `./test.sh`, that will run tests described in `test.c` file in qemu. (`qemu` and `cpio` must be installed).