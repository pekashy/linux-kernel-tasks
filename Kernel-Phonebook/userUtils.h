#include "common/user.h"

BDUSER* CreateUser(const char* firstName, const char* lastName, int age, const char* email, const char* phone);

BDUSER* AllocUser(void);

void FreeUser(BDUSER* pUser);

void CopyUser(BDUSER* dest, BDUSER* src);