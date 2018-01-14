/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Louis-Marie <Louis-Marie@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 10:46:02 by ljoly             #+#    #+#             */
/*   Updated: 2018/01/15 00:50:37 by Louis-Marie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_meta *meta = NULL;

static void *add_data(size_t size)
{
    int     i;
    void    *ptr;
    
    i = 1;
    if (size <= TINY_MAX_SIZE)
    {
        while (i < getpagesize() - meta[0].size_left)
        {
            if (meta[i].type == TINY_RANGE && meta[i].size_left >= size)
            {
                meta[i].size_left--;
                ptr = meta[i].ptr;
                break;
            }
            i++;
        }
        while (meta[i])
            i++;
        ptr =
    }
    // else if (size <= SMALL_MAX_SIZE)
    // {
    // }
    // else
    // {
    // }
}

static void allocate_meta(void)
{
    t_meta  *cpy;
    
    if (meta)
    {
        cpy = (t_meta *)mmap(0, sizeof(meta) + getpagesize() * sizeof(t_meta),
            PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
        cpy = (t_meta *)ft_memcpy(cpy, meta, getpagesize());
        if (munmap(meta, sizeof(meta))
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
    }
    ft_putendl("ALLOCATION META DONE");
}

void *ft_malloc(size_t size)
{
    void *ptr;

    ptr = NULL;
    if (size > SIZE_T_MAX - (2 * getpagesize()))
        return (NULL);
    if (!meta || (meta && !meta[0].size_left))
        allocate_meta(0);
    ptr = add_data(size);
    ft_putendl("AUTRE ALLOCATION\n");
    return (ptr);
}
