/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 10:46:02 by ljoly             #+#    #+#             */
/*   Updated: 2018/01/08 18:16:35 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_meta   *meta;

void    *ft_malloc(int size)
{
    meta = (t_meta*)mmap(0, size + 1, PROT_READ | PROT_WRITE,
    MAP_ANON | MAP_PRIVATE, -1, 0);
    return (meta);
}
