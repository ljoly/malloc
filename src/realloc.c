/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 19:48:45 by ljoly             #+#    #+#             */
/*   Updated: 2018/02/18 22:10:40 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void           *realloc(void *ptr, size_t size)
{
    size_t     i;
    void       *p;

    ft_putendl("realloc in");
    p = ptr;
    if (ptr)
    {
        if (meta)
        {
            i = 1;
            while (i < meta[0].type - meta[0].size)
            {
                if ((meta[i].type == TINY_BLOCK || meta[i].type == SMALL_BLOCK ||
                     meta[i].type == LARGE_REGION) &&
                    meta[i].ptr == (char *)ptr)
                {
                    if (meta[i].size < size)
                    {
                        p = malloc(size);
                        p = ft_memcpy(p, meta[i].ptr, sizeof(meta[i].ptr));
                        free(ptr);                        
                    }
                    return (p);
                }
                i++;
            }
        }
        // ft_printf("Pointer %p was not allocated.\n", ptr);
        // exit(-1);
    }
    ft_putendl("realloc out");
    return (malloc(size));
}