#include <stdlib.h>

int     main(void)
{
    int i;
    char *addr;

    i = 0;
    // ft_putendl("TEST1");
    while (i < 1024)
    {
        addr = (char*)malloc(1024);
        addr[0] = 42;
        // free(addr);
        i++;
    }
    // show_alloc_mem();        
    // ft_putnbr(mmap_count);
    // ft_putchar('\n');
    // ft_putnbr(new_alloc);
    // ft_putchar('\n');
    // ft_putnbr(pages);
    // ft_putchar('\n');
    return (0);
}
