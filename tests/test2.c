#include <unistd.h>
#include <stdlib.h>

int     main(void)
{
    int i;
    char *addr;

    i = 0;
    write(1, "TEST2\n", 6);
    while (i < 5)
    {
        addr = (char*)malloc(1024);
        addr[0] = 42;
        free(addr);
        i++;
    }
    return (0);
}
