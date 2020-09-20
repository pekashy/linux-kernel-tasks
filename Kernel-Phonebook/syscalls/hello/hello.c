#include <linux/kernel.h>

asmlinkage long __x64_sys_hello(void)
{
    printk("Hello world\n");
    return 0;
}