/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_meta.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:27:49 by ljoly             #+#    #+#             */
/*   Updated: 2018/03/05 18:41:41 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void            allocate_meta(void)
{
    t_meta      *cpy;
    int         meta_alloc_inbytes;
    size_t      previous_size_inbytes;

    // new_alloc++;

    meta_alloc_inbytes = (getpagesize() / sizeof(t_meta)) * sizeof(t_meta);
    // ft_putstr("META ALLOC IN BYTES = ");
    // ft_putnbr(meta_alloc_inbytes);
    // ft_putchar('\n');
    if (g_meta)
    {
        // ft_putendl("AN OTHER META ALLOCATION");
        previous_size_inbytes = g_meta[0].type * sizeof(t_meta);
        cpy = (t_meta *)mmap(0, previous_size_inbytes + meta_alloc_inbytes,        
        // cpy = (t_meta *)mmap(0, previous_size_inbytes + 2 * meta_alloc_inbytes,
            MMAP_FLAGS, -1, 0);
        // mmap_count++;
        // pages += (previous_size_inbytes / getpagesize() + (previous_size_inbytes % getpagesize() ? 1 : 0)) + 1;
        cpy = (t_meta *)ft_memcpy(cpy, g_meta, previous_size_inbytes);
        if (munmap(g_meta, previous_size_inbytes))
        {
            ft_putendl("ERROR");
        }
        else
        {
            g_meta = cpy;
            g_meta[0].type += getpagesize() / sizeof(t_meta);
            // g_meta[0].type += 2 * meta_alloc_inbytes;            
            g_meta[0].size = getpagesize() / sizeof(t_meta);
            // g_meta[0].size = 2 * meta_alloc_inbytes;
            // g_meta[2 * meta_alloc_inbytes - 1].type = 9;           
            // ft_putendl("NEW ALLOCATION SUCCESS");
        }
    }
    else
    {
        // ft_putendl("ALLOCATION META");
        // g_meta = (t_meta *)mmap(0, meta_alloc_inbytes, MMAP_FLAGS, -1, 0);
        g_meta = (t_meta *)mmap(0, 6 * meta_alloc_inbytes, MMAP_FLAGS, -1, 0);        
        // pages++;
        // mmap_count++;
        // g_meta[0].type = meta_alloc_inbytes / sizeof(t_meta);              
        g_meta[0].type = 6 * meta_alloc_inbytes / sizeof(t_meta);                      
        g_meta[0].size = g_meta[0].type - 1;
        // size_t    i;

        // i = 1;
        // while (i < (meta_alloc_inbytes / sizeof(t_meta)))
        // {
        //     ft_putnbr(i);
        //     ft_putchar(' ');            
        //     g_meta[i].type = 9;
        //     ft_putnbr(g_meta[i].type);
            
        //     ft_putchar('\n');
        //     i++;
        // }
        // ft_putnbr(g_meta[0].type);
        // ft_putendl("ALLOCATION META DONE");
    }
}