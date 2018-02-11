/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 19:48:45 by ljoly             #+#    #+#             */
/*   Updated: 2018/02/11 21:00:13 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void           *ft_realloc(void *ptr, size_t size)
{
    size_t     i;
    void       *p;

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
                        p = ft_malloc(size);
                        p = ft_memcpy(p, meta[i].ptr, sizeof(meta[i].ptr));
                        ft_free(ptr);                        
                    }
                    return (p);
                }
                i++;
            }
        }
        ft_printf("Pointer %p was not allocated.\n", ptr);
        exit(-1);
    }
    return (ft_malloc(size));
}