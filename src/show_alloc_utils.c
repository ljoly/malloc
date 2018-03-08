/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 22:16:07 by ljoly             #+#    #+#             */
/*   Updated: 2018/03/07 23:46:26 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_bool		is_in_region(t_show_mem mem, char *ptr)
{
	return (ptr - mem.region_ptr >= 0 &&
		ptr - mem.region_ptr < (long)mem.region_size);
}

t_bool		is_large(t_type type)
{
	return (type == LARGE_REGION);
}

t_bool      is_block(t_type type)
{
	return (type == TINY_BLOCK || type == SMALL_BLOCK);
}

void		get_region_size(size_t size, t_show_mem *mem)
{
	if (mem->region == TINY_REGION)
	{
		mem->region_size = T_REGION_SIZE;
	}
	else if (mem->region == SMALL_REGION)
	{
		mem->region_size = S_REGION_SIZE;
	}
	else if (mem->region == LARGE_REGION)
	{
		mem->region_size = size;
	}
}

