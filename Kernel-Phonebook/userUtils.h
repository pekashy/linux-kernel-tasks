#include "common/user.h"

USER* CreateUser(const char* firstName, const char* lastName, int age, const char* email, const char* phone);

USER* AllocUser(void);

void FreeUser(USER* pUser);

void CopyUser(USER* dest, USER* src);