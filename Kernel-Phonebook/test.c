#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <assert.h>
#include <string.h> 
#include "common/user.h"
#include <stdlib.h>

#define SYSCALL_HELLOWORLD 335
#define SYSCALL_ADDUSER 336
#define SYSCALL_GETUSER 337

USER AllocUser()
{
	USER checkuser;
	checkuser.email = calloc(1024, sizeof(char));
	checkuser.firstName = calloc(1024, sizeof(char));
	checkuser.lastName = calloc(1024, sizeof(char));
	checkuser.phone = calloc(1024, sizeof(char));
	memset(checkuser.firstName, 0, 1024*sizeof(char));
	memset(checkuser.email, 0, 1024*sizeof(char));
	memset(checkuser.lastName, 0, 1024*sizeof(char));
	memset(checkuser.phone, 0, 1024*sizeof(char));
	return checkuser;
}

void test_helloworld()
{
	assert(!syscall(SYSCALL_HELLOWORLD));
	printf("Test <Hello World> Passed!\n");
	sleep(5);
}

void test_adduser()
{
	USER testuser =
	{
		"John",
		"Doe",
		23,
		"johndoe@pp.cc",
		"11-22-33-44",
	};
	assert(!syscall(SYSCALL_ADDUSER, "John", "Doe", 23, "johndoe@pp.cc", "11-22-33-44"));
	printf("Test <Add User> Passed!\n");
	sleep(5);
}

void test_checkuser()
{
	USER checkuser = AllocUser();

	assert(!syscall(SYSCALL_ADDUSER, "John", "Doe", 23, "johndoe@pp.cc", "11-22-33-44"));
	long res = syscall(SYSCALL_GETUSER, "Doe", &checkuser);
	assert(!strcmp(checkuser.lastName, "Doe"));

	assert(!syscall(SYSCALL_ADDUSER, "John", "Wick", 43, "babayaga@pp.cc", "11-22-33-44"));
	res = syscall(SYSCALL_GETUSER, "Wick", &checkuser);
	assert(!strcmp(checkuser.lastName, "Wick"));
	assert(!strcmp(checkuser.firstName, "John"));
	assert(checkuser.age == 43);
	assert(!strcmp(checkuser.email, "babayaga@pp.cc"));
	assert(!strcmp(checkuser.phone, "11-22-33-44"));

	res = syscall(SYSCALL_GETUSER, "Doe", &checkuser);
	assert(!strcmp(checkuser.lastName, "Doe"));
	assert(!strcmp(checkuser.firstName, "John"));
	assert(checkuser.age == 23);
	assert(!strcmp(checkuser.email, "johndoe@pp.cc"));
	assert(!strcmp(checkuser.phone, "11-22-33-44"));

	printf("Test <Add and Get User> Passed!\n");


	sleep(5);
}

int test()
{
	test_helloworld();
	test_adduser();
	test_checkuser();
	printf("Tests Passed!\n");
	sleep(30);
}

int main(int argc, char *argv[])
{
	test();
	return 0;
}
