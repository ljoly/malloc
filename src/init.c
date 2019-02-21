/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 12:07:06 by ljoly             #+#    #+#             */
/*   Updated: 2019/02/21 17:54:57 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** The size to map is function of the smallest quantum allocable
*/

static size_t	quantum_size_to_map(size_t size)
{
	size_t		size_to_map;
	size_t		quantum;

	if (size == 0)
		size = 1;
	if (size <= TINY_MAX)
		quantum = TINY_QUANTUM;
	else if (size <= SMALL_MAX)
		quantum = SMALL_QUANTUM;
	else
		return (size);
	size_to_map = (size / quantum + ((size % quantum) ? 1 : 0)) * quantum;
	return (size_to_map);
}

void			init_request(t_req *r, size_t size)
{
	r->size_request = size;
	r->size_to_map = quantum_size_to_map(size);
	r->region = LARGE_REGION;
	r->block = LARGE_FREED;
	r->region_size = size;
	r->region_index = 0;
	r->index = 0;
	r->zone = NULL;
	if (r->size_to_map <= TINY_MAX)
	{
		r->region = TINY_REGION;
		r->region_size = T_REGION_SIZE;
		r->block = TINY_FREED;

		// ft_putendl("Req in TINY REGION");
	}
	else if (r->size_to_map <= SMALL_MAX)
	{
		r->region = SMALL_REGION;
		r->region_size = S_REGION_SIZE;
		r->block = SMALL_FREED;

		// ft_putendl("Req in SMALL REGION");
	}
}
