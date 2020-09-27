#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/list.h>
#include <linux/slab.h>


#define DEVICE_NAME "addressbook"

static int dev_open(struct inode*, struct file*);
static int dev_release(struct inode*, struct file*);
static ssize_t dev_read(struct file*, char*, size_t, loff_t*);
static ssize_t dev_write(struct file*, const char*, size_t, loff_t*);


typedef struct _user
{
	char* firstName;
	char* lastName;
	int age;
	char* email;
	char* phone;
} BDUSER;

BDUSER* gQueriedUser = NULL;

void KFreeUser(BDUSER* pUser)
{
	kzfree(pUser->email);
	kzfree(pUser->firstName);
	kzfree(pUser->lastName);
	kzfree(pUser->phone);
	kzfree(pUser);
	pUser = NULL;
}

BDUSER* KCloneUser(BDUSER* pUser)
{
	BDUSER* pNewUser = kmalloc(sizeof(BDUSER), GFP_KERNEL);
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

void KCopyUser(BDUSER* dest, BDUSER* src)
{
	strcpy(dest->firstName, src->firstName);   
	strcpy(dest->lastName, src->lastName);   
	strcpy(dest->email, src->email);   
	strcpy(dest->phone, src->phone);   
	dest->age = src->age;
}

typedef struct _dbEntry
{
	BDUSER* pUser;
	struct list_head list;
} DBENTRY;

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

BDUSER* GetUser(const char* surname)
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


int AddUser(BDUSER* pUser)
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

int ProcessAdd(const char* pBuffer)
{
	printk(KERN_INFO "Processing insertion of: '%s'\n", pBuffer);
	char* safeString = kzalloc(strlen(pBuffer), GFP_KERNEL);
	strcpy(safeString, pBuffer);
	char *token = strsep(&safeString, " "); // ID of operation
	printk(KERN_INFO "Op ID : '%s'\n", token);

   	const char* rFirstName = strsep(&safeString, " ");
	if(rFirstName == NULL)
	{
		kzfree(safeString);
		return -2;
	}
	printk(KERN_INFO ": '%s'\n", rFirstName);

	const char* rLastName = strsep(&safeString, " ");
	if(rLastName == NULL)	
	{
		kzfree(safeString);
		return -2;
	}

	printk(KERN_INFO ": '%s'\n", rLastName);

	const char* rAge = strsep(&safeString, " ");
	if(rAge == NULL)
	{
		kzfree(safeString);
		return -2;
	}
	printk(KERN_INFO ": '%s'\n", rAge);
	unsigned long nAge;
	int res = kstrtol(rAge, 10, &nAge);
	if(res)
	{
		printk(KERN_INFO "Failed to parse number %s with code %d\n", rAge, res);
		kzfree(safeString);
		return res;
	}
	const char* rEmail = strsep(&safeString, " ");
	if(rEmail == NULL)
	{
		kzfree(safeString);
		return -2;
	}
	printk(KERN_INFO ": '%s'\n", rEmail);

	const char* rPhone = strsep(&safeString, " ");
	if(rPhone == NULL)
	{
		kzfree(safeString);
		return -2;
	}
	printk(KERN_INFO ": '%s'\n", rPhone);

	BDUSER userSpaceAddressedUser = 
		{rFirstName,
		 rLastName,
		 nAge,
		 rEmail,
		 rPhone};
	BDUSER* pPersistentUser = KCloneUser(&userSpaceAddressedUser);
	kzfree(safeString);
	return AddUser(pPersistentUser);
}

int ProcessGet(const char* pBuffer)
{
	printk(KERN_INFO "Processing querying of: '%s'\n", pBuffer);
	char* safeString = kzalloc(strlen(pBuffer), GFP_KERNEL);
	strcpy(safeString, pBuffer);
	char *token = strsep(&safeString, " "); // ID of operation
	printk(KERN_INFO "Op ID : '%s'\n", token);
   	const char* rLastName = strsep(&safeString, " ");
	if(rLastName == NULL)
	{
		kzfree(safeString);
		return -2;
	}
	printk(KERN_INFO ": '%s'\n", rLastName);

	gQueriedUser = GetUser(rLastName);
	return gQueriedUser == NULL;
}

int ProcessDelete(const char* pBuffer)
{
	return 0;
}

static struct file_operations fops = {
	.open = dev_open,
	.read = dev_read,
	.write = dev_write,
	.release = dev_release,
};

static int major;

static int __init addressbook_init(void)
{
	printk(KERN_INFO "Address Book module has been loaded %d\n", major);
	major = register_chrdev(0, DEVICE_NAME, &fops);
	if(major < 0)
	{
		printk(KERN_ALERT "Address Book load failed");
	}
	printk(KERN_INFO "Address Book module has been loaded %d\n", major);
	return 0;
}

static void __exit addressbook_exit(void)
{
	unregister_chrdev(major, DEVICE_NAME);
	printk(KERN_INFO "Address Book module has been unloaded\n");
	return;
}

static int dev_open(struct inode* pInode, struct file* pFile)
{
	printk(KERN_INFO "Address Book device opened\n");
	return 0;
}

static int dev_release(struct inode* pInode, struct file* pFile)
{
	printk(KERN_INFO "Address Book device closed\n");
	return 0;
}

static ssize_t dev_read(struct file* pFile, char* pBuffer, size_t len, loff_t* offset)
{
	printk(KERN_ERR "Read attempt\n");
	int errors = 0;
	if(gQueriedUser == NULL)
	{
		return 0;
	}

	char* firstName;
	char* lastName;
	int age;
	char* email;
	char* phone;


	snprintf(pBuffer, len, "%s %s %d %s %s\0",
			gQueriedUser->firstName, gQueriedUser->lastName, gQueriedUser->age, gQueriedUser->email, gQueriedUser->phone);
	printk("%s\n", pBuffer);
	return errors == 0 ? strlen(pBuffer) : 0;
}

static ssize_t dev_write(struct file* pFile, const char* pBuffer, size_t len, loff_t* offset)
{
	if(strlen(pBuffer) < 3)
	{
		return -EFAULT;
	}
	int errors = 0;
	switch (*pBuffer)
	{
	case '1':
		errors = ProcessAdd(pBuffer);
		break;
	case '2':
		errors = ProcessGet(pBuffer);
		break;
	case '3':
		errors = ProcessDelete(pBuffer);
		break;
	default:
		errors = -2;
		break;
	}
	printk(KERN_ERR "Now read-only\n");
	return errors == 0 ? strlen(pBuffer) : -EFAULT;
}

module_init(addressbook_init);
module_exit(addressbook_exit);
