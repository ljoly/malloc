#include "malloc.h"

int     main(void)
{
    int i;
    char *addr;

    i = 0;
    while (i < 1024)
    {
        addr = (char*)ft_malloc(1024);
        addr[0] = 42;
        i++;
        if (meta[0].size == 5)
            show_alloc_mem();
    }
    return (0);
}