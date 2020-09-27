#include <linux/kernel.h>
#include <linux/syscalls.h>
#include "../kernel_common/userK.h"
#include "../kernel_common/db.h"

SYSCALL_DEFINE1(user_add, const BDUSER*, pPassedUser)
{
	BDUSER* pNewUser = KCloneUser(pPassedUser);
	printk("Add user:\n First Name: %s\n Last Name: %s\n: Age: %d\n Email: %s\n, Phone: %s\n", 
		pNewUser->firstName, pNewUser->lastName, pNewUser->age, pNewUser->email, pNewUser->phone);
	return AddUser(pNewUser);
}