/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 10:46:02 by ljoly             #+#    #+#             */
/*   Updated: 2019/02/24 16:47:55 by ljoly            ###   ########.fr       */
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
				r->region_index = i;
				r->region_ptr = g_meta[i].ptr;
				return (i);
			}
			i++;
		}
	}
	return (FALSE);
}

static size_t	get_available_block(t_req *r, t_type type)
{
	size_t		i;

	i = 1;
	while (i < g_meta[0].type - g_meta[0].size)
	{
		if ((g_meta[i].type == type || g_meta[i].type == type - 2) &&
			is_in_region(r->region_ptr, r->region_size_total, g_meta[i].ptr))
		{
			if (g_meta[i].type == type && g_meta[i].size >= r->size_to_map)
			{
				r->block_ptr = g_meta[i].ptr;
				return (r->block_index = i);
			}
			r->region_size_used += g_meta[i].size;
		}
		i++;
	}
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
		r->region_index = i;
		r->region_ptr = ptr;
		r->block = (r->block == TINY_FREED) ? TINY_BLOCK : SMALL_BLOCK;
		if (!g_meta[0].size)
		{
			allocate_meta();
		}
		map_zone(r, r->block, TRUE);
	}
	return (ptr);
}

static void		*get_available_zone(size_t size)
{
	void		*ptr;
	t_req		r;

	ptr = NULL;
	init_request(&r, size);
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
		return (r.block_ptr);
	}
	else
	{
		ptr = map_new_region(&r);
	}
	return (ptr);
}

void			*malloc(size_t size)
{
	void		*ptr;

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
	ptr = get_available_zone(size);
	pthread_mutex_unlock(mutex_sglton());
	return (ptr);
}
