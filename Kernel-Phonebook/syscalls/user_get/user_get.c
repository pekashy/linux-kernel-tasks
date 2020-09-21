#include <linux/kernel.h>
#include <linux/syscalls.h>
#include "../kernel_common/userK.h"
#include "../kernel_common/db.h"


SYSCALL_DEFINE2(user_get, const char*, surname, USER*, pOutputData)
{
	if(pOutputData == NULL)
	{
		return 1;
	}

	USER* foundUser = GetUser(surname);

	if(foundUser != NULL)
	{
		KCopyUser(pOutputData, foundUser);

		printk("Get user:\n First Name: %s\n Last Name: %s\n: Age: %d\n Email: %s\n, Phone: %s\n", 
			pOutputData->firstName, pOutputData->lastName, pOutputData->age, pOutputData->email, pOutputData->phone);

		return 0;
	}

	return 1;
}