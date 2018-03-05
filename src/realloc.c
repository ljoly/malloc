/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 19:48:45 by ljoly             #+#    #+#             */
/*   Updated: 2018/03/05 19:23:58 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void           *realloc(void *ptr, size_t size)
{
    size_t     i;
    void       *p;

    p = ptr;
    if (ptr)
    {
        if (g_meta)
        {
            i = 1;
            while (i < g_meta[0].type - g_meta[0].size)
            {
                if ((g_meta[i].type == TINY_BLOCK || g_meta[i].type == SMALL_BLOCK ||
                     g_meta[i].type == LARGE_REGION) &&
                    g_meta[i].ptr == (char *)ptr)
                {
                    if (g_meta[i].size < size)
                    {
                        p = malloc(size);
                        p = ft_memcpy(p, g_meta[i].ptr, g_meta[i].size);
                        free(ptr);                        
                    }
                    return (p);
                }
                i++;
            }
            return (NULL);
        }
    }
    return (malloc(size));
}