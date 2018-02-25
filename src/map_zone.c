/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_zone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 20:32:13 by ljoly             #+#    #+#             */
/*   Updated: 2018/02/25 22:57:20 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** Maps a requested zone (ie. region or block)
*/
void            map_zone(t_req *r, t_type type, t_bool new_block)
{
    int         i;

    i = g_meta[0].type - g_meta[0].size;
    if (type >= TINY_REGION)
    {
        g_meta[i].type = type;        
        g_meta[i].ptr = mmap(0, r->region_size, MMAP_FLAGS, -1, 0);
        // mmap_count++;
        // ft_printf("pages = %zu\n", pages);
        // ft_printf("r->region_size = %zu\n", r->region_size);
        // pages += (r->region_size / getpagesize() + ((r->region_size % getpagesize()) ? 1 : 0));
        // ft_printf("pages = %zu\n", pages);
        g_meta[i].size = r->size_to_map;
        r->zone = g_meta[i].ptr;
    }
    else if (new_block)
    {
        g_meta[i].type = type;        
        g_meta[i].ptr = r->zone;
        g_meta[i].size = r->size_to_map;
    }
    else
    {
        ft_putendl("MAP BLOCK");
        ft_putnbr(r->index);
        ft_putchar('\n');
        g_meta[r->index].type = type;
        g_meta[r->index].ptr = r->zone;
        g_meta[r->index].size = r->size_to_map;
        return;
    }
    g_meta[0].size--;
}