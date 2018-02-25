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
    }
    // ft_putnbr(mmap_count);
    // ft_putchar('\n');
    // ft_putnbr(new_alloc);
    // ft_putchar('\n');
    // ft_putnbr(pages);
    // ft_putchar('\n');
    return (0);
}
