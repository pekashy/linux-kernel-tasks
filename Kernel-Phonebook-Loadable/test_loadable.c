#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <assert.h>
#include <string.h> 
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void test_read()
{
    int fd = open("/dev/addressbook", O_RDONLY | O_NONBLOCK);
    if(fd < 0)
    {
		printf("Opening device for read failed: %d\n", fd);
        assert(0);
    }
	char* buffer = malloc(256);
	int rd = read(fd, buffer, 250);
	buffer[rd] = 0;
	assert(rd);
	printf("Test <Read> succeeded!: %s\n", buffer);
	free(buffer);
	close(fd);
}

void test_write()
{
    int fd = open("/dev/addressbook", O_RDWR | O_NONBLOCK);
    if(fd < 0)
    {
		printf("Opening device for write failed: %d\n", fd);
        assert(0);
    }
	char* buffer = malloc(256);
	int wr = write(fd, buffer, 250);
	assert(wr != -1);
	printf("Test <Write> succeeded!\n");
	free(buffer);
	close(fd);
}

void testAdd()
{
    int fd = open("/dev/addressbook", O_RDWR | O_NONBLOCK);
    if(fd < 0)
    {
		printf("Opening device for write failed: %d\n", fd);
        assert(0);
    }
    char* buffer = "1 John Wick 37 babayaga@bb.cc 11-22-33";
    int wr = write(fd, buffer, strlen(buffer));
	assert(wr == strlen(buffer));
	printf("Test <Add User> succeeded!\n");
    close(fd);
}

void testDelete()
{

}

void testGet()
{
    int fd = open("/dev/addressbook", O_RDWR | O_NONBLOCK);
    if(fd < 0)
    {
		printf("Opening device for write failed: %d\n", fd);
        assert(0);
    }
    char* buffer = "1 John Wick2 38 babayaga@bb.cc 11-22-33";
    int wr = write(fd, buffer, strlen(buffer));
	assert(wr == strlen(buffer));
	
    char* buffer3 = "2 Wick3";
    wr = write(fd, buffer3, strlen(buffer3));
	assert(wr != strlen(buffer3));

    char* buffer2 = "2 Wick2";
    wr = write(fd, buffer2, strlen(buffer2));
	assert(wr == strlen(buffer2));
    
    //Now ready to read user
    close(fd);
    fd = open("/dev/addressbook", O_RDONLY | O_NONBLOCK);
    if(fd < 0)
    {
		printf("Opening device for write failed: %d\n", fd);
        assert(0);
    }
	char* buffer4 = malloc(4096);
	int rd = read(fd, buffer4, 4096);
	buffer4[rd] = 0;
	assert(rd);
    assert(!strcmp(buffer4, "John Wick2 38 babayaga@bb.cc 11-22-33"));
    free(buffer4);
    close(rd);
    printf("Test <Add-Get User> succeeded!\n");
}

void test()
{
    //test_read();
	//test_write();
    testAdd();
    testGet();
}


int main()
{
    printf("Loadable!\n");
    test();
}