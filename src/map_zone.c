/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_zone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 20:32:13 by ljoly             #+#    #+#             */
/*   Updated: 2018/02/11 20:33:32 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** Maps a requested zone (ie. region or block)
*/
void            map_zone(t_req *r, t_type type, t_bool new_block)
{
    int         i;

    i = meta[0].type - meta[0].size;
    if (type >= TINY_REGION)
    {
        meta[i].type = type;        
        meta[i].ptr = mmap(0, r->region_size, MMAP_FLAGS, -1, 0);
        meta[i].size = r->size_to_map;
        r->zone = meta[i].ptr;
    }
    else if (new_block)
    {
        meta[i].type = type;        
        meta[i].ptr = r->zone;
        meta[i].size = r->size_to_map;
    }
    else
    {
        meta[r->index].type = type;
        meta[r->index].ptr = r->zone;
        meta[r->index].size = r->size_to_map;
    }
    meta[0].size--;
}