/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 19:22:18 by ljoly             #+#    #+#             */
/*   Updated: 2018/03/23 15:24:47 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		update_region_size(char *ptr, size_t size)
{
	size_t		i;
	size_t		region_size;

	i = 1;
	region_size = (size <= TINY_MAX ? T_REGION_SIZE : S_REGION_SIZE);
	while (i < g_meta[0].type - g_meta[0].size)
	{
		if ((g_meta[i].type == TINY_REGION || g_meta[i].type == SMALL_REGION) &&
				ptr - g_meta[i].ptr >= 0 &&
				ptr - g_meta[i].ptr < (long)region_size)
		{
			g_meta[i].size += size;
			break ;
		}
		i++;
	}
}

static void		free_block(int i)
{
	if (g_meta[i].type == TINY_BLOCK)
		g_meta[i].type = TINY_FREED;
	else if (g_meta[i].type == SMALL_BLOCK)
		g_meta[i].type = SMALL_FREED;
	else if (g_meta[i].type == LARGE_REGION)
		g_meta[i].type = LARGE_FREED;
}

void			free(void *ptr)
{
	size_t		i;

	pthread_mutex_lock(mutex_sglton());
	if (ptr)
	{
		if (g_meta)
		{
			i = 1;
			while (i < g_meta[0].type - g_meta[0].size)
			{
				if ((g_meta[i].type == TINY_BLOCK ||
							g_meta[i].type == SMALL_BLOCK ||
							g_meta[i].type == LARGE_REGION) &&
						g_meta[i].ptr == (char *)ptr)
				{
					free_block(i);
					if (g_meta[i].type != LARGE_FREED)
						update_region_size((char *)ptr, g_meta[i].size);
					break ;
				}
				i++;
			}
		}
	}
	pthread_mutex_unlock(mutex_sglton());
}
