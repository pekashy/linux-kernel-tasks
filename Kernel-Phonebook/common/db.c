#include "db.h"
#include<linux/slab.h>

DBENTRY* gDBRoot = NULL;
static LIST_HEAD(listOfUsers);

int AddUser(USER* pUser)
{
    if(pUser == NULL)
    {
        return 1;
    }

    DBENTRY* gDBEntry = kmalloc(sizeof(DBENTRY), GFP_KERNEL);
    gDBEntry->pUser = NULL;

    if(gDBRoot == NULL)
    {
        gDBRoot = gDBEntry;
        INIT_LIST_HEAD(&gDBRoot->list);
    }

    gDBEntry->pUser = pUser;
    list_add(&gDBEntry->list, &listOfUsers);
}