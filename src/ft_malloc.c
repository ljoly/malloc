/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 10:46:02 by ljoly             #+#    #+#             */
/*   Updated: 2018/01/22 01:14:42 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_meta *meta = NULL;

static void *add_data(size_t size)
{
    unsigned long   i;
    void            *ptr;
    t_bool          is_zone;

    i = 1;
    ptr = NULL;
    is_zone = FALSE;
    ft_putendl("ADD_DATA");
    if (size <= TINY_MAX_SIZE)
    {
        // Check if the zone was already allocated or not
        while (i <= getpagesize() - meta[0].size_left)
        {
            ft_putendl("BROWSE_META");
            if (meta[i].type == TINY_ZONE && meta[i].size_left >= size &&
                is_zone == FALSE)
            {
                is_zone = TRUE;
                meta[i].size_left--;
                ptr = meta[i].ptr;
                break;
            }
            i++;
        }
        while (meta[i].ptr)
            i++;
        ptr = meta[i].ptr;
    }
    // else if (size <= SMALL_MAX_SIZE)
    // {
    // }
    // else
    // {
    // }
    return ptr;
}

static void allocate_meta(void)
{
    t_meta  *cpy;
    
    if (meta)
    {
        ft_putendl("AUTRE ALLOCATION\n");
        cpy = (t_meta *)mmap(0, sizeof(meta) + getpagesize() * sizeof(t_meta),
            PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
        cpy = (t_meta *)ft_memcpy(cpy, meta, getpagesize());
        if (munmap(meta, sizeof(meta)))
        {
            ft_putendl("ERROR");
        }
        else
        {
            meta = cpy;
            meta[0].size_left = getpagesize();
            ft_putendl("NEW ALLOCATION SUCCESS");
        }
    }
    else
    {
        ft_putendl("ALLOCATION META");
        meta = (t_meta *)mmap(0, getpagesize() * sizeof(t_meta),
            PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
        ft_bzero(meta, sizeof(meta));
        meta[0].type = META;
        meta[0].ptr = NULL;
        meta[0].size_left = getpagesize() - 1;
        ft_putendl("ALLOCATION META DONE");
    }
}

void *ft_malloc(size_t size)
{
    void *ptr;

    ptr = NULL;
    ft_putendl("CALL");
    if (size > SIZE_T_MAX - (2 * getpagesize()))
        return (NULL);
    if (!meta || (meta && size > meta[0].size_left))
        allocate_meta();
    ptr = add_data(size);
    return (ptr);
}
