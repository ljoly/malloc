/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_region_size.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 20:16:40 by ljoly             #+#    #+#             */
/*   Updated: 2018/02/24 17:40:34 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void            update_region_size(char *ptr, size_t size)
{
    size_t      i;
    long        region_size;

    i = 1;
    // ft_putendl("region size in");
    region_size = (size <= TINY_MAX ? T_REGION_SIZE : S_REGION_SIZE);
    // ft_printf("region size = %zu\n", region_size);
    while (i < g_meta[0].type - g_meta[0].size)
    {
        if ((g_meta[i].type == TINY_REGION || g_meta[i].type == SMALL_REGION) &&
            ptr - g_meta[i].ptr >= 0 && ptr - g_meta[i].ptr < region_size)
        {
            // ft_putendl("region size out");
            g_meta[i].size += size;
            break ;
        }
        i++;
    }
}