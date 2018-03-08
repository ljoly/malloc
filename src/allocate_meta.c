/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_meta.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:27:49 by ljoly             #+#    #+#             */
/*   Updated: 2018/03/07 19:42:00 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		extend_meta(void)
{
	size_t		previous_size_inbytes;
	t_meta		*cpy;

	previous_size_inbytes = g_meta[0].type * sizeof(t_meta);
	cpy = (t_meta *)mmap(0, previous_size_inbytes + getpagesize(),
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
	if (g_meta)
	{
		extend_meta();
	}
	else
	{
		g_meta = (t_meta *)mmap(0, 10 * getpagesize(), MMAP_FLAGS, -1, 0);
		g_meta[0].type = 10 * getpagesize() / sizeof(t_meta);
		g_meta[0].size = g_meta[0].type - 1;
	}
}
