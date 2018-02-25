#include "malloc.h"

int     main(void)
{
    int i;
    char *addr;

    i = 0;
    while (i < 2)
    {
        ft_putendl("AVANT");
        addr = (char*)malloc(1024);
        ft_putendl("APRES");
        addr[0] = 42;
        free(addr);
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
