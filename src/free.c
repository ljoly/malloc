/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 19:22:18 by ljoly             #+#    #+#             */
/*   Updated: 2018/02/18 22:12:37 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

// MUNMAP EMPTY REGIONS

void        free(void *ptr)
{
    size_t  i;

    ft_putendl("free in");
    if (ptr)
    {
        if (meta)
        {
            i = 1;
            while (i < meta[0].type - meta[0].size)
            {
                ft_putendl("free loop");
                if ((meta[i].type == TINY_BLOCK || meta[i].type == SMALL_BLOCK ||
                     meta[i].type == LARGE_REGION) &&
                    meta[i].ptr == (char *)ptr)
                {
                    ft_putendl("free condition");
                    if (meta[i].type == TINY_BLOCK)
                        meta[i].type = TINY_FREED;
                    else if (meta[i].type == SMALL_BLOCK)
                        meta[i].type = SMALL_FREED;
                    else if (meta[i].type == LARGE_REGION)
                        meta[i].type = LARGE_FREED;
                    if (meta[i].type != LARGE_FREED)
                    {
                        ft_putendl("free update");
                        update_region_size((char *)ptr, meta[i].size);
                    }
                    ft_putendl("free return");
                    return;
                }
                i++;
            }
        }
        // ft_printf("Pointer %p was not allocated and can not be freed.\n", ptr);
        // exit(-1);
    }
    ft_putendl("free out");
}