#include <unistd.h>
#include <stdlib.h>

int     main(void)
{
    int i;
    char *addr;

    i = 0;
    write(1, "TEST1\n", 6);
    while (i < 1024)
    {
        addr = (char*)malloc(1024);
        addr[0] = 42;
        i++;
    }
    return (0);
}
