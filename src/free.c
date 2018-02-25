/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 19:22:18 by ljoly             #+#    #+#             */
/*   Updated: 2018/02/25 22:53:26 by ljoly            ###   ########.fr       */
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
        if (g_meta)
        {
            i = 1;
            while (i < g_meta[0].type - g_meta[0].size)
            {
                // ft_putendl("free loop");
                if ((g_meta[i].type == TINY_BLOCK || g_meta[i].type == SMALL_BLOCK ||
                     g_meta[i].type == LARGE_REGION) &&
                    g_meta[i].ptr == (char *)ptr)
                {
                    // ft_putendl("free condition");
                    if (g_meta[i].type == TINY_BLOCK)
                        g_meta[i].type = TINY_FREED;
                    else if (g_meta[i].type == SMALL_BLOCK)
                        g_meta[i].type = SMALL_FREED;
                    else if (g_meta[i].type == LARGE_REGION)
                        g_meta[i].type = LARGE_FREED;
                    if (g_meta[i].type != LARGE_FREED)
                    {
                        // ft_putendl("free update");
                        update_region_size((char *)ptr, g_meta[i].size);
                    }
                    // show_alloc_mem();
                    ft_putendl("free out");
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