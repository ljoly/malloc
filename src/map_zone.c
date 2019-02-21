/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_zone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 20:32:13 by ljoly             #+#    #+#             */
/*   Updated: 2019/02/21 17:52:58 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		update_block(t_req *r, t_type type)
{
	g_meta[r->index].type = type;
	g_meta[r->index].ptr = r->zone;
	// g_meta[r->index].size = r->size_to_map;
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
		g_meta[i].size = r->region_size;
		// g_meta[i].size = r->size_to_map;
		g_meta[i].size_request = r->region_size;
		r->zone = g_meta[i].ptr;
		g_meta[0].size--;
	}
	else if (new_block)
	{
		// ft_putstr("Need to add Block ");
		// ft_putnbr(i - 1);
		// ft_putchar('\n');
		g_meta[i].type = type;
		g_meta[i].ptr = r->zone;
		g_meta[i].size = r->size_to_map;
		g_meta[i].size_request = r->size_request;
		// 		ft_putstr("size to remove = ");
		// ft_putnbr(r->size_to_map);
		// ft_putchar('\n');
		g_meta[r->region_index].size -= r->size_to_map;
		// ft_putstr("r->region_index = ");
		// ft_putnbr(r->region_index);
		// ft_putchar('\n');
		// ft_putstr("meta.[r->region_index].size = ");
		// ft_putnbr(g_meta[r->region_index].size);
		// ft_putchar('\n');
		g_meta[0].size--;
	}
	else
	{
		g_meta[r->region_index].size -= g_meta[r->index].size;
		update_block(r, type);
	}
}
