#include <linux/kernel.h>
#include <linux/syscalls.h>
#include "../kernel_common/userK.h"
#include "../kernel_common/db.h"


SYSCALL_DEFINE1(user_del, const char*, surname)
{
	return DeleteUser(surname);
}