#pragma once

#include <linux/list.h>

#include "user.h"

typedef struct _dbEntry
{
    USER* pUser;
    struct list_head list;
} DBENTRY;

int AddUser(USER* pUser);
USER* GetUser(const char* surname);
