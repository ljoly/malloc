/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 10:46:02 by ljoly             #+#    #+#             */
/*   Updated: 2018/01/29 19:07:48 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_meta *meta = NULL;

static void      map_region(t_type type, size_t region_size)
{
    int         i;

    meta[0].size_left--;
    i = getpagesize() - meta[0].size_left - 1;
    meta[i].type = type;
    meta[i].ptr = mmap(0, region_size, MMAP_FLAGS, -1, 0);
    ft_putendl("REGION ALLOCATED");
}

/*
** Check if the required zone (regions or block) was already allocated
*/ 
static t_meta   *get_available_zone(t_type type, size_t size, size_t quantum)
{
    unsigned long   i;
    size_t          size_to_map;
    t_meta          *ptr;

    i = 1;
    ptr = NULL;    
    size_to_map = size / quantum;
    if (size % quantum)
        size_to_map++;
    size_to_map *= quantum;                                   // HERE
    while (i < getpagesize() - meta[0].size_left)
    {
        if (meta[i].type == type && meta[i].size_left >= size_to_map)
        {
            return meta + i;
            // ptr = meta[i].ptr;
            break;
        }
            i++;
        }
}

static void *map_data(size_t size)
{
    int     i;
    void    *ptr;
    int     blocks;

    i = getpagesize() - meta[0].size_left;
    ptr = NULL;
    ft_putendl("ADD_DATA");
    if (size <= TINY_MAX)
    {
        if ((ptr = get_available_zone(TINY_REGION, size, TINY_QUANTUM)))
        {
            // get_available_block(); >>> get_available_zone() for both bocks and zones
        }
        else
        {
            map_region(TINY_REGION, T_REGION_SIZE);
            ptr = meta[i].ptr;
            blocks = size / TINY_QUANTUM;
            if (size % TINY_QUANTUM)
                blocks++;
            meta[i].size_left = T_REGION_SIZE - blocks * TINY_QUANTUM;
            meta[0].size_left--;            
            meta[++i].type = TINY_BLOCK;
            meta[i].ptr = ptr;
        }
    }
    // else if (size <= SMALL_MAX_SIZE)
    // {
    // }
    // else
    // {
        // LARGE
    // }
    return ptr;
}

static void allocate_meta(void)
{
    t_meta *cpy;

    if (meta)
    {
        ft_putendl("AUTRE ALLOCATION\n");
        cpy = (t_meta *)mmap(0, sizeof(meta) + getpagesize() * sizeof(t_meta),
            MMAP_FLAGS, -1, 0);
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
            MMAP_FLAGS, -1, 0);
        ft_bzero(meta, sizeof(meta));
        meta[0].type = META;
        meta[0].size_left = getpagesize() - 1;
        ft_putendl("ALLOCATION META DONE");
    }
}

static void     print(void)
{
    unsigned long         i;

    i = 0;
    while (i < getpagesize() - meta[0].size_left)
    {

        printf("\nmeta[%lu]:\ntype: %d\nptr: %p\nsize_left: %zu\n\n", i, meta[i].type, meta[i].ptr, meta[i].size_left);
        i++;
    }
}

void *ft_malloc(size_t size)
{
    void *ptr;

    ptr = NULL;
    ft_putendl("CALL");
    if (size > SIZE_T_MAX - (2 * getpagesize()))
        return (NULL);
    if (!meta || (meta && !meta[0].size_left))
        allocate_meta();
    ptr = map_data(size);
    print();
    return (ptr);
}
