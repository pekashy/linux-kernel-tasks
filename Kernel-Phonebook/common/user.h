#pragma once

typedef struct _user
{
    char* firstName;
    char* lastName;
    int age;
    char* email;
    char* phone;
} USER;

USER* CreateUser(const char* firstName, const char* lastName, int age, const char* email, const char* phone);