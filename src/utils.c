/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 16:12:50 by ljoly             #+#    #+#             */
/*   Updated: 2019/02/24 16:49:33 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_bool		is_in_region(char *region_ptr, long region_size, char *ptr)
{
	return (ptr - region_ptr >= 0 &&
		ptr - region_ptr < region_size);
}

t_bool		is_large(t_type type)
{
	return (type == LARGE_REGION);
}

t_bool		is_block(t_type type)
{
	return (type == TINY_BLOCK || type == SMALL_BLOCK);
}
