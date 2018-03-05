#include <unistd.h>

int     main(void)
{
    int i;

    i = 0;
    write(1, "TEST0\n", 6);
    while (i < 1024)
    {
        i++;
    }
    return (0);
}