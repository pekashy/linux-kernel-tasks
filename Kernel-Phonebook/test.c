#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <assert.h>
#include <string.h> 
#include "common/user.h"
#include <stdlib.h>
#include "userUtils.h"

#define SYSCALL_HELLOWORLD 335
#define SYSCALL_ADDUSER 336
#define SYSCALL_GETUSER 337
#define SYSCALL_DELUSER 338

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
	assert(!syscall(SYSCALL_ADDUSER, &testuser));
	printf("Test <Add User> Passed!\n");
	sleep(5);
}

void test_checkuser()
{
	USER checkuser = *AllocUser();

	strcpy(checkuser.firstName, "John");   
	strcpy(checkuser.lastName, "Doe");   
	strcpy(checkuser.email, "johndoe@pp.cc");   
	strcpy(checkuser.phone, "11-22-33-44");   
	checkuser.age = 23;

	assert(!syscall(SYSCALL_ADDUSER, &checkuser));
	long res = syscall(SYSCALL_GETUSER, "Doe", &checkuser);
	printf("%s %li!\n", checkuser.firstName, res);
	assert(!strcmp(checkuser.lastName, "Doe"));

	strcpy(checkuser.lastName, "Wick");   
	strcpy(checkuser.email, "babayaga@pp.cc");   
	checkuser.age = 43;
	assert(!syscall(SYSCALL_ADDUSER, &checkuser));
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

int test_delete()
{
	USER checkuser = *AllocUser();

	strcpy(checkuser.firstName, "John");   
	strcpy(checkuser.lastName, "DelDoe");   
	strcpy(checkuser.email, "johndeldoe@pp.cc");   
	strcpy(checkuser.phone, "11-22-33-44");   
	checkuser.age = 23;

	assert(syscall(SYSCALL_DELUSER, "DelDoe"));
	sleep(2);
	assert(syscall(SYSCALL_GETUSER, "DelDoe", &checkuser));
	sleep(2);
	assert(!syscall(SYSCALL_ADDUSER, &checkuser));
	sleep(2);
	assert(!syscall(SYSCALL_GETUSER, "DelDoe", &checkuser));
	sleep(2);
	assert(!syscall(SYSCALL_DELUSER, "DelDoe"));
	sleep(2);
	assert(syscall(SYSCALL_GETUSER, "DelDoe", &checkuser));
	sleep(2);

	printf("Test <Delete and Check User> Passed!\n");
	sleep(5);
}

int test()
{
	test_helloworld();
	test_adduser();
	test_checkuser();
	test_delete();
	printf("Tests Passed!\n");
	sleep(30);
}

int main(int argc, char *argv[])
{
	test();
	return 0;
}
