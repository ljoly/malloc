/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_zone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 20:32:13 by ljoly             #+#    #+#             */
/*   Updated: 2019/02/19 12:03:51 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		update_block(t_req *r, t_type type)
{
	g_meta[r->index].type = type;
	g_meta[r->index].ptr = r->zone;
	g_meta[r->index].size = r->size_to_map;
	g_meta[r->index].size_request = r->size_request;
}

/*
** Maps a requested zone (ie. region or block)
*/

void			map_zone(t_req *r, t_type type, t_bool new_block)
{
	int			i;

	i = g_meta[0].type - g_meta[0].size;
	if (type >= TINY_REGION)
	{
		// ft_putstr("MAP NEW REGION: ");
		// if (type == TINY_REGION)
			// ft_putendl("TINY");
		// if (type == SMALL_REGION)
			// ft_putendl("SMALL");

		g_meta[i].type = type;
		g_meta[i].ptr = mmap(0, r->region_size, MMAP_FLAGS, -1, 0);
		g_meta[i].size = r->size_to_map;
		g_meta[i].size_request = r->region_size;
		r->zone = g_meta[i].ptr;
		g_meta[0].size--;
	}
	else if (new_block)
	{
		g_meta[i].type = type;
		g_meta[i].ptr = r->zone;
		g_meta[i].size = r->size_to_map;
		g_meta[i].size_request = r->size_request;
		g_meta[0].size--;
	}
	else
		update_block(r, type);
}
