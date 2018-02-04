/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 10:46:02 by ljoly             #+#    #+#             */
/*   Updated: 2018/02/04 21:58:26 by ljoly            ###   ########.fr       */
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
** Maps a requested zone (ie. region or block)
*/
static void      map_zone(t_req *r, t_type type, t_bool new_block)
{
    int         i;

    i = meta[0].type - meta[0].size_left;
    if (type >= TINY_REGION)
    {
        ft_printf("TYPE = %d, INDEX = %d\n", type, i);
        meta[i].type = type;        
        meta[i].ptr = mmap(0, r->region_size, MMAP_FLAGS, -1, 0);
        r->zone = meta[i].ptr;
    }
    else if (new_block)
    {
        meta[i].type = type;        
        meta[i].ptr = r->zone;
    }
    else
    {
        meta[r->index].type = type;
        meta[r->index].ptr = r->zone;
    }
    meta[0].size_left--;
    ft_printf("SIZE LEFT = %zu\n", meta[0].size_left);
    ft_putendl("REGION MAPPED");
}

// 

/*
** Checks if the required zone (ie. region OR block) was already allocated and returns it
*/ 
static size_t   get_available_zone(t_req *r, t_type type)
{
	size_t      i;

    i = 1;
    if (type == TINY_REGION || type == SMALL_REGION || type == LARGE_REGION)
    {   
        ft_printf("TYPE ASKED = %d\n", type);
        while (i < meta[0].type - meta[0].size_left)
        {
            ft_printf("TYPE IN META = %d\n", meta[i].type);
            if (meta[i].type == type && meta[i].size_left >= r->size_to_map)
            {
                ft_putendl("AARRRFF");
                r->zone = meta[i].ptr + (r->region_size - meta[i].size_left);
                meta[i].size_left -= r->size_to_map;
                return i;
            }
            i++;
        }
    }
    else
    {
        while (i < meta[0].type - meta[0].size_left)
        {
            if (meta[i].type == type && meta[i].ptr == r->zone)
                return (r->index = i);
            i++;
        }
    }
    return 0;
}

static char *map_data(size_t size)
{
    int     i;
    char    *ptr;
    t_req   r;

    ptr = NULL;
    r.size_to_map = quantum_size_to_map(size);
    // r.region = LARGE_REGION;                // DEAL WITH LARGE LATER
    // r.block = LARGE_FREED;
    r.region_size = size;
    r.index = 0;    
    if (size <= TINY_MAX)
    {
        r.region = TINY_REGION;
        r.region_size = T_REGION_SIZE;
        r.block = TINY_FREED;
    }
    else if (size <= SMALL_MAX)
    {
        r.region = SMALL_REGION;
        r.region_size = S_REGION_SIZE;
        r.block = SMALL_FREED;
    }
    if ((get_available_zone(&r, r.region)))
    {
        ft_putendl("AVAILABLE REGION FOUND !");
        if ((get_available_zone(&r, r.block)))
        {
            ft_putendl("AVAILABLE BLOCK FOUND !");
            map_zone(&r, r.block, FALSE);
        }
        else
            map_zone(&r, r.block, TRUE);
        return r.zone;
    }
    else
    {
        i = meta[0].type - meta[0].size_left;
        map_zone(&r, r.region, FALSE);
        ptr = meta[i].ptr;
        meta[i].size_left = r.region_size - r.size_to_map;
        map_zone(&r, r.block, TRUE);
        
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
    // t_meta *cpy;
    int     size;

    size = getpagesize() / sizeof(t_meta);
    // if (meta)
    // {
    //     ft_putendl("AUTRE ALLOCATION\n");
    //     cpy = (t_meta *)mmap(0, sizeof(meta) + getpagesize() * sizeof(t_meta),
    //         MMAP_FLAGS, -1, 0);
    //     cpy = (t_meta *)ft_memcpy(cpy, meta, getpagesize());
    //     if (munmap(meta, sizeof(meta)))
    //     {
    //         ft_putendl("ERROR");
    //     }
    //     else
    //     {
    //         meta = cpy;
            // meta[0].type += getpagesize() / sizeof(t_meta);
    //         meta[0].ptr = (char*)meta + getpagesize();
    //         meta[0].size_left = getpagesize();
    //         ft_putendl("NEW ALLOCATION SUCCESS");
    //     }
    // }
    // else
    // {
        ft_putendl("ALLOCATION META");
        meta = (t_meta *)mmap(0, size, MMAP_FLAGS, -1, 0);
        ft_bzero(meta, sizeof(meta));
        meta[0].type = size;
        meta[0].ptr = (char*)meta;
        meta[0].size_left = size - 1;
        ft_putendl("ALLOCATION META DONE");
    // }
}

static void     print(void)
{
    unsigned long         i;

    i = 0;
    while (i < meta[0].type - meta[0].size_left)
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
    ptr = (void*)map_data(size);
    print();
    return (ptr);
}
