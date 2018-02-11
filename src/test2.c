#include "malloc.h"

int     main(void)
{
    char *s;

    s = (char *)ft_malloc(sizeof(char) * 40);
    s[0] = 's';
    ft_printf("%s\n", s);
    ft_printf("address s = %p\n", s);

    // ft_free(s);
    s = ft_realloc(s, 993);
    ft_printf("%s\n", s);
    ft_printf("address s = %p\n", s);    
    show_alloc_mem();
    return (0);
}