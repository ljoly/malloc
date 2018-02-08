/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_memory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 17:55:47 by ljoly             #+#    #+#             */
/*   Updated: 2018/02/08 17:56:56 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void            show_alloc_mem(void)
{
    size_t      i;

    i = 0;
    while (i < meta[0].type - meta[0].size)
    {
        printf("\nmeta[%lu]:\ntype: %d\nptr: %p\nsize: %zu\n\n", i, meta[i].type, meta[i].ptr, meta[i].size);
        i++;
    }
}