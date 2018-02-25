/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_memory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 17:55:47 by ljoly             #+#    #+#             */
/*   Updated: 2018/02/25 23:35:02 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void            show_alloc_mem(void)
{
    size_t      i;

    pthread_mutex_lock(&g_mutex);    
    i = 0;
    while (i < g_meta[0].type - g_meta[0].size)
    {
        ft_putstr("\nmeta[");
        ft_putnbr(i);
        ft_putstr("]:\ntype: ");
        ft_putnbr(g_meta[i].type);
        ft_putstr("\nsize: ");
        ft_putnbr(g_meta[i].size);
        ft_putstr("\n\n");
        // printf("\nmeta[%lu]:\ntype: %d\nptr: %p\nsize: %zu\n\n", i, g_meta[i].type, g_meta[i].ptr, g_meta[i].size);
        i++;
    }
    pthread_mutex_lock(&g_mutex);    
}