/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 10:46:02 by ljoly             #+#    #+#             */
/*   Updated: 2018/01/11 19:00:50 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_meta *meta = NULL;

// static void fill_range(t_meta *meta)
// {

// }

// static void *add_data(t_meta *meta)
// {

// }

static void allocate_meta(t_meta *meta)
{
    ft_putendl("PREMIERE ALLOCATION\n");
    meta = (t_meta *)mmap(0, getpagesize() * sizeof(t_meta),
            PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    ft_bzero(meta, sizeof(meta));
    ft_putendl("PREMIERE ALLOCATION DONE");
}

void *ft_malloc(size_t size)
{
    void *ptr;

    ptr = NULL;
    if (size > SIZE_T_MAX - (2 * getpagesize()))
        return (NULL);
    if (!meta)
    {
        allocate_meta(meta);
    }
    else
    {
        // ptr = add_data(meta);
        ft_putendl("AUTRE ALLOCATION\n");
    }
    return (ptr);
}
