#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int fd = open("myfileasdasd.txt", O_RDWR | O_CREAT | O_APPEND, 0777);
    char buff[] = "Donizete";
    int written = write(fd, buff, sizeof(buff));
    close(fd);
    return EXIT_SUCCESS;
}