#include "user.h"
#include<linux/slab.h>

USER* CreateUser(const char* firstName, const char* lastName, int age, const char* email, const char* phone)
{
    USER* pNewUser = kmalloc(sizeof(USER), GFP_KERNEL);
    pNewUser->firstName = firstName;
    pNewUser->lastName = lastName;
    pNewUser->age = age;
    pNewUser->email = email;
    pNewUser->phone = phone;
    return pNewUser;
}