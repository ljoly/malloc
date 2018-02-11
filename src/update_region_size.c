/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_region_size.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 20:16:40 by ljoly             #+#    #+#             */
/*   Updated: 2018/02/11 20:18:24 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void            update_region_size(char *ptr, size_t size)
{
    size_t      i;
    long        region_size;

    i = 1;
    region_size = (size <= TINY_MAX ? T_REGION_SIZE : S_REGION_SIZE);
    while (i < meta[0].type - meta[0].size)
    {
        if ((meta[i].type == TINY_REGION || meta[i].type == SMALL_REGION) &&
            ptr - meta[i].ptr >= 0 && ptr - meta[i].ptr < region_size)
        {
            meta[i].size += size;
            break ;
        }
        i++;
    }
}