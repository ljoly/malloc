/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 10:46:02 by ljoly             #+#    #+#             */
/*   Updated: 2018/02/08 18:27:57 by ljoly            ###   ########.fr       */
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

    ft_printf("SIZE ASKED: %zu\n", size);
    if (size == 0)
        size = 1;
    if (size <= TINY_MAX)
        quantum = TINY_QUANTUM;
    else if (size <= SMALL_MAX)
        quantum = SMALL_QUANTUM;
    else
        return size;
    ft_printf("QUANTUM SIZE: %zu\n", quantum);
    size_to_map = (size / quantum + ((size % quantum) ? 1 : 0)) * quantum;
    return size_to_map;
}

/*
** Maps a requested zone (ie. region or block)
*/
static void      map_zone(t_req *r, t_type type, t_bool new_block)
{
    int         i;

    i = meta[0].type - meta[0].size;
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
        meta[i].size = r->size_asked;
    }
    else
    {
        meta[r->index].type = type;
        meta[r->index].ptr = r->zone;
        meta[r->index].size = r->size_asked;
    }
    meta[0].size--;
    ft_printf("SIZE LEFT = %zu\n", meta[0].size);
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
    ft_printf("TYPE ASKED = %d\n", type);    
    if (type == TINY_REGION || type == SMALL_REGION || type == LARGE_REGION)
    {   
        while (i < meta[0].type - meta[0].size)
        {
            ft_printf("TYPE IN META = %d\n", meta[i].type);
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
            ft_printf("TYPE IN META = %d\n", meta[i].type);            
            if (meta[i].type == type && meta[i].ptr == r->zone)
                return (r->index = i);
            i++;
        }
    }
    return 0;
}

static void    init_request(t_req  *r, size_t size)
{
    r->size_asked = size;
    r->size_to_map = quantum_size_to_map(size);
    ft_printf("SIZE TO MAP: %zu\n", r->size_to_map);    
    r->region = LARGE_REGION;
    r->block = LARGE_FREED;
    r->region_size = r->size_asked;
    r->index = 0;
    if (r->size_asked <= TINY_MAX)
    {
        r->region = TINY_REGION;
        r->region_size = T_REGION_SIZE;
        r->block = TINY_FREED;
    }
    else if (r->size_asked <= SMALL_MAX)
    {
        r->region = SMALL_REGION;
        r->region_size = S_REGION_SIZE;
        r->block = SMALL_FREED;
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
            map_zone(&r, r.block, TRUE);
        return (r.zone);
    }
    else
    {
        i = meta[0].type - meta[0].size;
        map_zone(&r, r.region, FALSE);
        ptr = meta[i].ptr;
        meta[i].size = r.region_size - r.size_to_map;
        map_zone(&r, r.block, TRUE);
        
    }
    return (ptr);
}

static void     allocate_meta(void)
{
    // t_meta *cpy;
    int         size;

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
        meta[0].size = size - 1;
        ft_putendl("ALLOCATION META DONE");
    // }
}

void            *ft_malloc(size_t size)
{
    void        *ptr;

    ptr = NULL;
    ft_putendl("------------------------------MALLOC_CALLING");
    // if (size > SIZE_T_MAX - (2 * getpagesize()))
        // return (NULL);
    if (!meta || (meta && !meta[0].size))
        allocate_meta();
    ptr = (void*)map_data(size);
    show_alloc_mem();
    return (ptr);
}
