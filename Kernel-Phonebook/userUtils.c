#include "userUtils.h"
#include <string.h>
#include <stdlib.h>

// Deprecated
BDUSER* CreateUser(const char* firstName, const char* lastName, int age, const char* email, const char* phone)
{
	BDUSER* pNewUser = malloc(sizeof(BDUSER));
	pNewUser->firstName = firstName;
	pNewUser->lastName = lastName;
	pNewUser->age = age;
	pNewUser->email = email;
	pNewUser->phone = phone;
	return pNewUser;
}

BDUSER* AllocUser(void)
{
	BDUSER* pNewUser = (BDUSER*) malloc(sizeof(BDUSER));
	pNewUser->email = calloc(1024, sizeof(char));
	pNewUser->firstName = calloc(1024, sizeof(char));
	pNewUser->lastName = calloc(1024, sizeof(char));
	pNewUser->phone = calloc(1024, sizeof(char));
	memset(pNewUser->firstName, 0, 1024*sizeof(char));
	memset(pNewUser->email, 0, 1024*sizeof(char));
	memset(pNewUser->lastName, 0, 1024*sizeof(char));
	memset(pNewUser->phone, 0, 1024*sizeof(char));
	return pNewUser;
}
