/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 22:16:07 by ljoly             #+#    #+#             */
/*   Updated: 2019/02/24 16:29:22 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		print_region(t_show_mem mem)
{
	if (mem.region == TINY_REGION)
	{
		ft_putstr("TINY: ");
	}
	else if (mem.region == SMALL_REGION)
	{
		ft_putstr("SMALL: ");
	}
	else if (mem.region == LARGE_REGION)
	{
		ft_putendl("LARGE: ");
		return ;
	}
	ft_putstr("0x");
	ft_print_hex((size_t)mem.region_ptr, 1);
	ft_putchar('\n');
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
