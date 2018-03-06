/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_memory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 17:55:47 by ljoly             #+#    #+#             */
/*   Updated: 2018/03/06 14:10:00 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void show_alloc_mem(void)
{
    size_t i;

    pthread_mutex_lock(&g_mutex);
    if (g_meta)
    {
        i = 0;
        ft_putstr("\nmeta[0].size = ");
        ft_putnbr(g_meta[0].size);
        ft_putstr("\n\n");
        while (i < g_meta[0].type - g_meta[0].size)
        {
            ft_putstr("\nmeta[");
            ft_putnbr(i);
            ft_putstr("]:\ntype: ");
            ft_putnbr(g_meta[i].type);
            ft_putstr("\nptr: ");
            ft_print_hex((size_t)g_meta[i].ptr, 0);
            ft_putstr("\nsize: ");
            ft_putnbr(g_meta[i].size);
            ft_putstr("\n\n");

            i++;
        }
    }
    pthread_mutex_lock(&g_mutex);
}