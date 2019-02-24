/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 10:46:02 by ljoly             #+#    #+#             */
/*   Updated: 2019/02/24 16:27:54 by ljoly            ###   ########.fr       */
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

				// ft_putendl("FOUND available region");

				r->region_index = i;
				r->region_ptr = g_meta[i].ptr;

				// ft_putstr("region_total_size = ");
				// ft_putnbr(r->region_size_total);
				// ft_putchar('\n');

				// ft_putstr("region_size_used = ");
				// ft_putnbr(g_meta[i].size);
				// ft_putchar('\n');

				// ft_putstr("region_ptr = ");
				// ft_print_hex((size_t)r->region_ptr, 1);
				// ft_putchar('\n');
				return (i);
			}
			i++;
		}

		// ft_putendl("NOT FOUND available region");

	}
	return (FALSE);
}

static size_t	get_available_block(t_req *r, t_type type)
{
	size_t		i;

	i = 1;
	// ft_putstr("\nLooking for block ");
	// if (type == TINY_FREED)
	// 	ft_putendl("TINY FREED...");
	// if (type == SMALL_FREED)
	// 	ft_putendl("SMALL FREED...");
	while (i < g_meta[0].type - g_meta[0].size)
	{
		if ((g_meta[i].type == type || g_meta[i].type == type - 2) &&
			is_in_region(r->region_ptr, r->region_size_total, g_meta[i].ptr))
		{
			if (g_meta[i].type == type && g_meta[i].size >= r->size_to_map)
			{
				// ft_putstr("...FOUND Block ");
				// ft_putnbr(i - 1);
				// ft_putchar('\n');
				r->block_ptr = g_meta[i].ptr;
				return (r->block_index = i);
			}
			r->region_size_used += g_meta[i].size;
		}
		i++;
	}

	// ft_putendl("...NOT FOUND");


	return (FALSE);
}

static char		*map_new_region(t_req *r)
{
	size_t		i;
	char		*ptr;

		// ft_putendl("Map new region");


	i = g_meta[0].type - g_meta[0].size;

	// 		ft_putstr("i = ");
	// 	ft_putnbr(i);
	// ft_putchar('\n');
	
	map_zone(r, r->region, FALSE);
	ptr = g_meta[i].ptr;

		// 	ft_putstr("region_size = ");
		// ft_putnbr(g_meta[i].size);
		// ft_putchar('\n');
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

	// ft_putstr("MALLOC: ");
	// ft_putnbr(size);
	// ft_putchar('\n');
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

	// show_alloc_mem();
	// ft_putendl("\n\n");
	return (ptr);
}
