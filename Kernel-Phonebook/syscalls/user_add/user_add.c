#include <linux/kernel.h>
#include <linux/syscalls.h>
#include "../../common/user.h"
#include "../../common/db.h"

SYSCALL_DEFINE5(user_add, const char*, firstName, const char*, lastName, int, age, const char*, email, const char*, phone)
{
    printk("Add user:\n First Name: %s\n Last Name: %s\n: Age: %d\n Email: %s\n, Phone: %s\n", 
        firstName, lastName, age, email, phone);

    USER* newUser = CreateUser(firstName, lastName, age, email, phone);
    return AddUser(newUser);
}