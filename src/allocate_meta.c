/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_meta.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:27:49 by ljoly             #+#    #+#             */
/*   Updated: 2018/02/15 17:27:17 by ljoly            ###   ########.fr       */
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
    if (meta)
    {
        ft_putendl("AN OTHER META ALLOCATION\n");
        previous_size_inbytes = meta[0].type * sizeof(t_meta);
        cpy = (t_meta *)mmap(0, previous_size_inbytes + meta_alloc_inbytes,
            MMAP_FLAGS, -1, 0);
        // mmap_count++;
        // pages += (previous_size_inbytes / getpagesize() + (previous_size_inbytes % getpagesize() ? 1 : 0)) + 1;
        // ft_printf("pages = %zu\n", pages);
        cpy = (t_meta *)ft_memcpy(cpy, meta, previous_size_inbytes);
        if (munmap(meta, previous_size_inbytes))
        {
            ft_putendl("ERROR");
        }
        else
        {
            meta = cpy;
            meta[0].type += getpagesize() / sizeof(t_meta);
            meta[0].size = getpagesize() / sizeof(t_meta);
            // ft_printf("meta[0] = %zu\nsize = %zu\n", meta[0].type, meta[0].size);
            ft_putendl("NEW ALLOCATION SUCCESS");
        }
    }
    else
    {
        ft_putendl("ALLOCATION META");
        meta = (t_meta *)mmap(0, meta_alloc_inbytes, MMAP_FLAGS, -1, 0);
        // pages++;
        // ft_printf("pages premiere fois = %zu\n", pages);
        // mmap_count++;
        ft_bzero(meta, meta_alloc_inbytes);  
        meta[0].type = getpagesize() / sizeof(t_meta);              
        meta[0].size = meta[0].type - 1;
        ft_putendl("ALLOCATION META DONE");
    }
}