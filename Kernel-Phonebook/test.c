#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
         long int amma = syscall(548);
         printf("System call sys_hello returned %ld\n", amma);
         sleep(999999);
         return 0;
}
