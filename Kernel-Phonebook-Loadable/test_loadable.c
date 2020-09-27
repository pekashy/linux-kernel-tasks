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
// Open the device in non-blocking mode

void test_read()
{
    int fd = open("/dev/addressbook", O_RDONLY | O_NONBLOCK);
    if(fd < 0)
    {
		printf("Opening device for read failed: %d\n", fd);
        assert(0);  // handle error
    }
	char* buffer = malloc(256);
	int rd = read(fd, buffer, 250);
	buffer[rd] = 0;
	assert(rd);
	printf("Test read succeeded!: %s\n", buffer);
	free(buffer);
	close(fd);
}

void test_write()
{
    int fd = open("/dev/addressbook", O_RDWR | O_NONBLOCK);
    if(fd < 0)
    {
		printf("Opening device for write failed: %d\n", fd);
        assert(0);  // handle error
    }
	char* buffer = malloc(256);
	int wr = write(fd, buffer, 250);
	assert(wr != -1);
	//printf("Test write succeeded!: %s\n",);
	free(buffer);
	close(fd);
}

/*
void test_write()
{
    // Try to write some data
    ssize_t written = write(fd, "data", 4);
    if(written >= 0)
        ;  // handle successful write (which might be a partial write!)
    else if(errno == EWOULDBLOCK)
        ;  // handle case where the write would block
    else
        ;  // handle real error

    // Reading data is similar

}
*/
int main()
{
    printf("Loadable!\n");
	test_read();
	test_write();
}