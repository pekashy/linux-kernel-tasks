#include "userK.h"
#include <linux/slab.h>

void KFreeUser(USER* pUser)
{
	kzfree(pUser->email);
	kzfree(pUser->firstName);
	kzfree(pUser->lastName);
	kzfree(pUser->phone);
	kzfree(pUser);
	pUser = NULL;
}

USER* KCloneUser(USER* pUser)
{
	USER* pNewUser = kmalloc(sizeof(USER), GFP_KERNEL);
	pNewUser = kmalloc(sizeof(char)*1024, GFP_KERNEL);
	pNewUser->email = kmalloc(sizeof(char)*1024, GFP_KERNEL);
	pNewUser->firstName = kmalloc(sizeof(char)*1024, GFP_KERNEL);
	pNewUser->lastName = kmalloc(sizeof(char)*1024, GFP_KERNEL);
	pNewUser->phone = kmalloc(sizeof(char)*1024, GFP_KERNEL);
	strcpy(pNewUser->firstName, pUser->firstName);   
	strcpy(pNewUser->lastName, pUser->lastName);   
	strcpy(pNewUser->email, pUser->email);   
	strcpy(pNewUser->phone, pUser->phone);   
	pNewUser->age = pUser->age;
	return pNewUser;
}

void KCopyUser(USER* dest, USER* src)
{
	strcpy(dest->firstName, src->firstName);   
	strcpy(dest->lastName, src->lastName);   
	strcpy(dest->email, src->email);   
	strcpy(dest->phone, src->phone);   
	dest->age = src->age;
}