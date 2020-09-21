#include "db.h"
#include <linux/slab.h>

static DBENTRY* DBRoot = NULL;
static LIST_HEAD(listOfUsers);

USER* GetUser(const char* surname)
{
    if(!DBRoot)
    {
        return NULL;
    }

    DBENTRY* DBEntry = NULL;
    struct list_head* position = NULL;

    list_for_each(position, &listOfUsers)
    {
        DBEntry = container_of(position, DBENTRY, list);
        printk("User: %s %s ", DBEntry->pUser->lastName, surname);
        if(!strcmp(DBEntry->pUser->lastName, surname))
        {
            printk("MATCHED\n");
            return DBEntry->pUser;
        }
        printk("NOT MATCHED\n");
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