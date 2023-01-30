#include <unistd.h>

#define STD_INPUT 0
#define STD_OUTPUT 1
#define STD_ERR 2

int main(int argc, char *argv[])
{

    char buffer[1024];
    while (1)
    {
        int n_read = read(STD_INPUT, buffer, 1024);
        (void)write(STD_OUTPUT, buffer, n_read);
    }
    return 0;
}