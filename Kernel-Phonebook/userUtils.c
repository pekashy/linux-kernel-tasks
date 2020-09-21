#include "userUtils.h"
#include <string.h>
#include <stdlib.h>

// Deprecated
USER* CreateUser(const char* firstName, const char* lastName, int age, const char* email, const char* phone)
{
	USER* pNewUser = malloc(sizeof(USER));
	pNewUser->firstName = firstName;
	pNewUser->lastName = lastName;
	pNewUser->age = age;
	pNewUser->email = email;
	pNewUser->phone = phone;
	return pNewUser;
}

USER* AllocUser(void)
{
	USER* pNewUser = (USER*) malloc(sizeof(USER));
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
