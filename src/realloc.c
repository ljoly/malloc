/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 19:48:45 by ljoly             #+#    #+#             */
/*   Updated: 2018/03/08 16:53:25 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		*find_ptr(void *ptr, size_t size)
{
	size_t		i;
	void		*p;

	i = 1;
	p = ptr;
	while (i < g_meta[0].type - g_meta[0].size)
	{
		if ((g_meta[i].type == TINY_BLOCK || g_meta[i].type == SMALL_BLOCK ||
					g_meta[i].type == LARGE_REGION) &&
				g_meta[i].ptr == (char *)ptr)
		{
			if (g_meta[i].size < size)
			{
				p = malloc(size);
				p = ft_memcpy(p, g_meta[i].ptr, g_meta[i].size);
				free(ptr);
			}
			return (p);
		}
		i++;
	}
	return (NULL);
}

void			*realloc(void *ptr, size_t size)
{
	void		*p;

	pthread_mutex_lock(&g_mutex);
	p = NULL;
	if (ptr)
	{
		if (g_meta)
		{
			if (!size)
			{
				p = malloc(TINY_QUANTUM);
				free(ptr);
			}
			else
				p = find_ptr(ptr, size);
		}
	}
	else
	{
		p = malloc(size);
	}
	pthread_mutex_unlock(&g_mutex);
	return (p);
}
