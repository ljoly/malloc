/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_memory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 17:55:47 by ljoly             #+#    #+#             */
/*   Updated: 2019/02/24 16:49:18 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void			print_block(t_show_blocks to_print, t_show_blocks *last)
{
	ft_putstr("0x");
	ft_print_hex((size_t)to_print.start, 1);
	ft_putstr(" - 0x");
	ft_print_hex((size_t)to_print.end, 1);
	ft_putstr(": ");
	ft_putnbr(to_print.size);
	ft_putendl(" bytes");
	last->start = to_print.start;
	last->end = to_print.end;
	last->size = to_print.size;
}

static void			sort_blocks(t_show_blocks *to_print, t_show_blocks *last,
	t_meta meta)
{
	to_print->start = meta.ptr;
	to_print->end = meta.ptr + meta.size_request;
	to_print->size = meta.size_request;
	print_block(*to_print, last);
	to_print->start += meta.size;
}

static void			print_mem(t_show_mem mem)
{
	t_show_blocks	last;
	t_show_blocks	to_print;
	size_t			i;

	i = 1;
	print_region(mem);
	last.start = NULL;
	to_print.start = mem.region_ptr;
	while (i < g_meta[0].type - g_meta[0].size)
	{
		if ((is_large(g_meta[i].type) && is_large(mem.region)) ||
			((is_block(g_meta[i].type) &&
				is_in_region(mem.region_ptr, mem.region_size, g_meta[i].ptr))))
		{
			if ((is_large(mem.region) && g_meta[i].ptr > last.start) ||
				(g_meta[i].ptr > last.start && g_meta[i].ptr <= to_print.start))
			{
				sort_blocks(&to_print, &last, g_meta[i]);
				if (mem.region != LARGE_REGION)
					i = 0;
			}
		}
		i++;
	}
}

static void			sort_regions(t_show_mem *mem)
{
	size_t			i;

	i = 1;
	while (i < g_meta[0].type - g_meta[0].size)
	{
		if (g_meta[i].type == mem->region)
		{
			get_region_size(g_meta[i].size, mem);
			mem->region_ptr = g_meta[i].ptr;
			print_mem(*mem);
			if (is_large(mem->region))
				break ;
		}
		i++;
	}
}

void				show_alloc_mem(void)
{
	size_t			i;
	t_show_mem		mem;

	pthread_mutex_lock(mutex_sglton());
	if (g_meta)
	{
		i = 1;
		mem.region = TINY_REGION;
		while (mem.region <= LARGE_REGION)
		{
			sort_regions(&mem);
			mem.region++;
		}
	}
	pthread_mutex_unlock(mutex_sglton());
}
