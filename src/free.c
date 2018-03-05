/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 19:22:18 by ljoly             #+#    #+#             */
/*   Updated: 2018/03/05 19:17:21 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void     update_region_size(char *ptr, size_t size)
{
    size_t      i;
    size_t      region_size;

    i = 1;
    // ft_putendl("region size in");
    region_size = (size <= TINY_MAX ? T_REGION_SIZE : S_REGION_SIZE);
    while (i < g_meta[0].type - g_meta[0].size)
    {
        if ((g_meta[i].type == TINY_REGION || g_meta[i].type == SMALL_REGION) &&
            ptr - g_meta[i].ptr >= 0 && ptr - g_meta[i].ptr < (long)region_size)
        {
            // ft_putendl("region size out");
            g_meta[i].size += size;
            // if (g_meta[i].size == region_size)
            // {
            //     ft_putendl("LOL");
            //     unmap_blocks(g_meta[i].ptr, region_size);                
            //     munmap(g_meta[i].ptr, region_size);
            //     g_meta[i].type = NO_TYPE;
            //     g_meta[i].size = 0;
            //     g_meta[0].size++;
            // }
            break ;
        }
        i++;
    }
}

void        free(void *ptr)
{
    size_t  i;

    // ft_putendl("free in");
    pthread_mutex_lock(&g_mutex);
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
                    // ft_putstr("index found = ");
                    // ft_putnbr(i);
                    // ft_putchar('\n');
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
                    // ft_putendl("free out");
                    return;
                }
                i++;
            }
        }
        // ft_printf("Pointer %p was not allocated and can not be freed.\n", ptr);
        // exit(-1);
    }
    pthread_mutex_lock(&g_mutex);
    // ft_putendl("free out");
}