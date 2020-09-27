#pragma once

#include <linux/list.h>

#include "../../common/user.h"

typedef struct _dbEntry
{
	BDUSER* pUser;
	struct list_head list;
} DBENTRY;

int AddUser(BDUSER* pUser);
BDUSER* GetUser(const char* surname);
int DeleteUser(const char* surname);