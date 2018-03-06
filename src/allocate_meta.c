/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_meta.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:27:49 by ljoly             #+#    #+#             */
/*   Updated: 2018/03/06 14:59:25 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		extend_meta(int meta_alloc_inbytes)
{
	size_t		previous_size_inbytes;
	t_meta		*cpy;

	previous_size_inbytes = g_meta[0].type * sizeof(t_meta);
	cpy = (t_meta *)mmap(0, previous_size_inbytes + meta_alloc_inbytes,
			MMAP_FLAGS, -1, 0);
	cpy = (t_meta *)ft_memcpy(cpy, g_meta, previous_size_inbytes);
	if (munmap(g_meta, previous_size_inbytes))
	{
		ft_putendl_fd("Error: munmap", 2);
		exit(-1);
	}
	else
	{
		g_meta = cpy;
		g_meta[0].type += getpagesize() / sizeof(t_meta);
		g_meta[0].size = getpagesize() / sizeof(t_meta);
	}
}

void			allocate_meta(void)
{
	int			meta_alloc_inbytes;

	meta_alloc_inbytes = (getpagesize() / sizeof(t_meta)) * sizeof(t_meta);
	if (g_meta)
	{
		extend_meta(meta_alloc_inbytes);
	}
	else
	{
		g_meta = (t_meta *)mmap(0, 6 * meta_alloc_inbytes, MMAP_FLAGS, -1, 0);
		g_meta[0].type = 6 * meta_alloc_inbytes / sizeof(t_meta);
		g_meta[0].size = g_meta[0].type - 1;
	}
}
