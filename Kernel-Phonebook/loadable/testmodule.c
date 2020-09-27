#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init testmodule_init(void)
{
    printk(KERN_INFO "Rickroll module has been loaded\n");
    return 0;
}

static void __exit testmodule_exit(void)
{
    printk(KERN_INFO "Rickroll module has been unloaded\n");
    return;
}

module_init(testmodule_init);
module_exit(testmodule_exit);
