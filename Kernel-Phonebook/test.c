#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <assert.h>

#include "common/user.h"

#define SYSCALL_HELLOWORLD 335
#define SYSCALL_ADDUSER 336

void test_helloworld()
{
	assert(!syscall(SYSCALL_HELLOWORLD));
	printf("Test <Hello World> Passed!\n");
	sleep(3);
}

void test_adduser()
{
	USER testuser =
	{
		"John",
		"Doe",
		23,
		"johndoe@pp.cc",
		"11-22-33-44"
	};
	assert(!syscall(SYSCALL_ADDUSER, "John", "Doe", 23, "johndoe@pp.cc", "11-22-33-44"));
	printf("Test <Add User> Passed!\n");
	sleep(3);
}

int test()
{
	test_helloworld();
	sleep(3);
	test_adduser();
	printf("Tests Passed!\n");
}

int main(int argc, char *argv[])
{
	test();
	sleep(30);
	return 0;
}
