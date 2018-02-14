/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 10:46:02 by ljoly             #+#    #+#             */
/*   Updated: 2018/02/14 23:32:34 by ljoly            ###   ########.fr       */
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

    if (size == 0)
        size = 1;
    if (size <= TINY_MAX)
        quantum = TINY_QUANTUM;
    else if (size <= SMALL_MAX)
        quantum = SMALL_QUANTUM;
    else
        return size;
    size_to_map = (size / quantum + ((size % quantum) ? 1 : 0)) * quantum;
    return size_to_map;
}

/*
** Checks if the required zone (ie. region OR block) was already allocated
*/ 
static size_t   get_available_zone(t_req *r, t_type type)
{
	size_t      i;

    i = 1;
    if (type == TINY_REGION || type == SMALL_REGION || type == LARGE_FREED)
    {
        while (i < meta[0].type - meta[0].size)
        {
            if (meta[i].type == type && meta[i].size >= r->size_to_map)
            {
                r->zone = meta[i].ptr + (r->region_size - meta[i].size);
                meta[i].size -= r->size_to_map;
                return i;
            }
            i++;
        }
    }
    else
    {
        while (i < meta[0].type - meta[0].size)
        {
            if (meta[i].type == type && meta[i].ptr == r->zone)
                return (r->index = i);
            i++;
        }
    }
    return 0;
}

static void    init_request(t_req  *r, size_t size)
{
    r->size_to_map = quantum_size_to_map(size);
    r->region = LARGE_REGION;
    r->block = LARGE_FREED;
    r->region_size = size;
    r->index = 0;
    if (r->size_to_map <= TINY_MAX)
    {
        r->region = TINY_REGION;
        r->region_size = T_REGION_SIZE;
        r->block = TINY_FREED;
    }
    else if (r->size_to_map <= SMALL_MAX)
    {
        r->region = SMALL_REGION;
        r->region_size = S_REGION_SIZE;
        r->block = SMALL_FREED;
    }
}    

static void     allocate_meta(void)
{
    t_meta      *cpy;
    int         size;

    size = getpagesize() / sizeof(t_meta);
    if (meta)
    {
        ft_putendl("AN OTHER META ALLOCATION\n");
        cpy = (t_meta *)mmap(0, meta[0].type * sizeof(t_meta) + size,
            MMAP_FLAGS, -1, 0);
        cpy = (t_meta *)ft_memcpy(cpy, meta, meta[0].type * sizeof(t_meta));
        ft_printf("SIZE OF META = %zu\n", meta[0].type * sizeof(t_meta));
        if (munmap(meta, meta[0].type * sizeof(t_meta)))
        {
            ft_putendl("ERROR");
        }
        else
        {
            meta = cpy;
            meta[0].type += size;
            meta[0].size = size;
            ft_putendl("NEW ALLOCATION SUCCESS");
        }
    }
    else
    {
        ft_putendl("ALLOCATION META");
        meta = (t_meta *)mmap(0, size * sizeof(t_meta), MMAP_FLAGS, -1, 0);
        ft_bzero(meta, size * sizeof(t_meta));  
        meta[0].type = size;              
        meta[0].size = size - 1;
        ft_putendl("ALLOCATION META DONE");
    }
}

static      char *map_data(size_t size)
{
    char    *ptr;
    t_req   r;
    int     i;

    ptr = NULL;
    init_request(&r, size);
    if ((get_available_zone(&r, r.region)))
    {
        if ((get_available_zone(&r, r.block)))
        {
            map_zone(&r, r.block, FALSE);
        }
        else
        {
            r.block = (r.block == TINY_FREED) ? TINY_BLOCK : SMALL_BLOCK; 
            map_zone(&r, r.block, TRUE);
        }
        return (r.zone);
    }
    else
    {
        i = meta[0].type - meta[0].size;
        map_zone(&r, r.region, FALSE);
        ptr = meta[i].ptr;
        if (r.region != LARGE_REGION)
        {
            meta[i].size = r.region_size - r.size_to_map;
            r.block = (r.block == TINY_FREED) ? TINY_BLOCK : SMALL_BLOCK;
            if (!meta[0].size)
                allocate_meta();
            map_zone(&r, r.block, TRUE);
        }
    }
    return (ptr);
}


void            *ft_malloc(size_t size)
{
    void        *ptr;

    ptr = NULL;
    if (!meta || (meta && !meta[0].size))
        allocate_meta();
    ptr = (void*)map_data(size);
    return (ptr);
}
