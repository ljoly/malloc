/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 10:46:02 by ljoly             #+#    #+#             */
/*   Updated: 2019/02/21 15:25:07 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_meta			*g_meta = NULL;

static size_t	get_available_region(t_req *r, t_type type)
{
	size_t		i;

	i = 1;
	if (type == TINY_REGION || type == SMALL_REGION || type == LARGE_FREED)
	{
		while (i < g_meta[0].type - g_meta[0].size)
		{
			if (g_meta[i].type == type && g_meta[i].size >= r->size_to_map)
			{

				ft_putendl("FOUND available region");

				r->zone = g_meta[i].ptr + (r->region_size - g_meta[i].size);
				//update size later with the block size and not size_to_map
				// g_meta[i].size -= r->size_to_map;
				ft_putstr("ptr found = ");
				ft_print_hex((size_t)r->zone, 1);
				ft_putchar('\n');
				return (i);
			}
			i++;
		}

		ft_putendl("NOT FOUND available region");

	}
	return (FALSE);
}

static size_t	get_available_block(t_req *r, t_type type)
{
	size_t		i;

	i = 1;
	ft_putstr("Looking for block ");
	if (type == TINY_FREED)
		ft_putendl("TINY FREED...");
	if (type == SMALL_FREED)
		ft_putendl("SMALL FREED...");
	while (i < g_meta[0].type - g_meta[0].size)
	{
		if (g_meta[i].type == type && g_meta[i].ptr == r->zone)
		{
			ft_putstr("...FOUND Block ");
			ft_putnbr(i - 1);
			ft_putchar('\n');
			return (r->index = i);
		}
		i++;
	}

	ft_putendl("...NOT FOUND");


	return (FALSE);
}

static char		*map_new_region(t_req *r)
{
	size_t		i;
	char		*ptr;

	i = g_meta[0].type - g_meta[0].size;
	map_zone(r, r->region, FALSE);
	ptr = g_meta[i].ptr;
	if (r->region != LARGE_REGION)
	{
		g_meta[i].size = r->region_size - r->size_to_map;
		r->block = (r->block == TINY_FREED) ? TINY_BLOCK : SMALL_BLOCK;
		if (!g_meta[0].size)
		{
			allocate_meta();
		}
		map_zone(r, r->block, TRUE);
	}
	return (ptr);
}

static char		*map_data(size_t size)
{
	char		*ptr;
	t_req		r;

	ptr = NULL;
	init_request(&r, size);
	// get region index to update it later
	if ((get_available_region(&r, r.region)))
	{
		if ((get_available_block(&r, r.block)))
		{
			r.block = (r.block == TINY_FREED) ? TINY_BLOCK : SMALL_BLOCK;
			map_zone(&r, r.block, FALSE);
		}
		else
		{
			r.block = (r.block == TINY_FREED) ? TINY_BLOCK : SMALL_BLOCK;
			map_zone(&r, r.block, TRUE);
		}
		return (r.zone);
	}
	else
	{
		
		ft_putendl("Did not find available region/Map new one");
	
		ptr = map_new_region(&r);
	}
	return (ptr);
}

void			*malloc(size_t size)
{
	void		*ptr;

	ft_putstr("MALLOC: ");
	ft_putnbr(size);
	ft_putchar('\n');
	pthread_mutex_lock(mutex_sglton());
	if ((ssize_t)size < 0)
	{
		pthread_mutex_unlock(mutex_sglton());
		return (NULL);
	}
	ptr = NULL;
	if (!g_meta || (g_meta && !g_meta[0].size))
	{
		allocate_meta();
	}
	ptr = (void*)map_data(size);
	pthread_mutex_unlock(mutex_sglton());

	show_alloc_mem();
	ft_putendl("\n");
	return (ptr);
}
