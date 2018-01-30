/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 10:46:02 by ljoly             #+#    #+#             */
/*   Updated: 2018/01/30 20:22:24 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_meta *meta = NULL;

/*
** The size to map is function of the smallest quantum allocable
*/
static size_t   quantum_size_to_map(size_t size)
{
    size_t      size_to_map;
    size_t      quantum;

    if (size <= TINY_MAX)
        quantum = TINY_QUANTUM;
    else if (size <= SMALL_MAX)
        quantum = SMALL_QUANTUM;
    else
        return size;
    size_to_map = (size / quantum + (size % quantum) ? 1 : 0) * quantum;
    return size_to_map;
}

/*
** Map zone (ie. region or block)
*/
static void      map_zone(t_type type, void *at)
{
    int         i;

    meta[0].size_left--;
    i = getpagesize() - meta[0].size_left - 1;
    meta[i].type = type;
    if (type == TINY_REGION || type == SMALL_REGION || type == LARGE_REGION)
    {
        meta[i].ptr = mmap(0, region_size, MMAP_FLAGS, -1, 0);
    }
    else
    {
        meta[i].ptr = // HERE
    }
    ft_putendl("REGION MAPPED");
}

/*
** Check if the required zone (ie. region OR block) was already allocated
*/ 
static t_meta   *get_available_zone(t_type type, size_t size_to_map, size_t region_size)
{
	unsigned long   i;

    i = 1;
    while (i < getpagesize() - meta[0].size_left)
    {
        if (meta[i].type == type && meta[i].size_left >= size_to_map)
        {
            return meta[i].ptr + ;
            // ptr = meta[i].ptr;
        }
            i++;
    }
    return NULL;
}

static void *map_data(size_t size)
{
    int     i;
    void    *ptr;
    size_t  size_to_map;
    t_type  region;
    t_type  block;
    size_t  region_size;

    i = getpagesize() - meta[0].size_left;
    ptr = NULL;
    size_to_map = quantum_size_to_map(size);
    region = LARGE_REGION;
    block = LARGE_FREED;
    region_size = size;
    if (size <= TINY_MAX)
    {
        region = TINY_REGION;
        region_size = T_REGION_SIZE;
        block = TINY_FREED;
    }
    else if (size <= SMALL_MAX)
    {
        region = SMALL_REGION;
        region_size = S_REGION_SIZE;
        block = SMALL_FREED;
    }
    if ((ptr = get_available_zone(region, size_to_map, region_size)))
    {
        ft_putendl("AVAILABLE REGION FOUND !");
        if ((ptr = get_available_zone(block, size_to_map, )))
            ft_putendl("AVAILABLE BLOCK FOUND !");
            map_zone(block);
        else
            map_zone(block);
    }
    else
    {
        map_zone(region, NULL);
        ptr = meta[i].ptr;
        meta[i].size_left = T_REGION_SIZE - size_to_map;
        meta[0].size_left--;            
        meta[++i].type = TINY_BLOCK;
        meta[i].ptr = ptr;
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
        meta[0].ptr = &meta[0].ptr;
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
    ft_putendl("------------------------------MALLOC_CALLING");
    if (size > SIZE_T_MAX - (2 * getpagesize()))
        return (NULL);
    if (!meta || (meta && !meta[0].size_left))
        allocate_meta();
    ptr = map_data(size);
    print();
    return (ptr);
}
