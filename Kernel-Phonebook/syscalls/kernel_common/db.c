#include "db.h"
#include <linux/slab.h>
#include "userK.h"

static DBENTRY* DBRoot = NULL;
static LIST_HEAD(listOfUsers);

int FreeEntry(DBENTRY* pEntry)
{
	if(!pEntry)
	{
		return 1;
	}

	KFreeUser(pEntry->pUser);
	kzfree(pEntry);
	pEntry = NULL;
	return 0;
}

struct list_head* GetEntry(const char* surname)
{
	if(!DBRoot)
	{
		return NULL;
	}

	struct list_head* position = NULL;

	list_for_each(position, &listOfUsers)
	{
		DBENTRY* DBEntry = container_of(position, DBENTRY, list);
		printk("User: %s %s ", DBEntry->pUser->lastName, surname);
		if(!strcmp(DBEntry->pUser->lastName, surname))
		{
			printk("MATCHED\n");
			return position;
		}
		printk("NOT MATCHED\n");
	}

	return NULL;
}

int DeleteUser(const char* surname)
{
	if(!DBRoot)
	{
		return 1;
	}

	struct list_head* position = GetEntry(surname);

	if(position)
	{
		DBENTRY* DBEntry = container_of(position, DBENTRY, list);
		list_del(position);
		return FreeEntry(DBEntry);
	}
	return 1;
}

USER* GetUser(const char* surname)
{
	if(DBRoot == NULL)
	{
		return NULL;
	}
	
	struct list_head* position = GetEntry(surname);

	if(position)
	{
		DBENTRY* DBEntry = container_of(position, DBENTRY, list);
		return DBEntry->pUser;
	}

	return NULL;
}


int AddUser(USER* pUser)
{
	if(pUser == NULL)
	{
		return 1;
	}

	DBENTRY* DBEntry = kmalloc(sizeof(DBENTRY), GFP_KERNEL);
	DBEntry->pUser = NULL;

	if(DBRoot == NULL)
	{
		DBRoot = DBEntry;
		INIT_LIST_HEAD(&DBRoot->list);
	}

	DBEntry->pUser = pUser;
	list_add(&DBEntry->list, &listOfUsers);

	return 0;
}