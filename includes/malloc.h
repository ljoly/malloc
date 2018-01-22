/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 10:52:44 by ljoly             #+#    #+#             */
/*   Updated: 2018/01/21 21:26:30 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "libft.h"
# include <sys/mman.h>

# define TINY_MAX_SIZE 992
# define SMALL_MAX_SIZE 1000000000

/*
** Blocks are subzones of Zones. Meta is an array of meta data.
*/
typedef enum        e_type
{
	META,
    TINY_BLOCK,
    SMALL_BLOCK,
    LARGE_BLOCK,
	TINY_ZONE,
	SMALL_ZONE,
	LARGE_ZONE
}                   t_type;

typedef struct      s_meta
{
	t_type			type;
	void			*ptr;
	size_t			size_left;
}                   t_meta;

extern t_meta   	*meta;

void				*ft_malloc(size_t size);
void 				*malloc(size_t size);
void 				*realloc(void *ptr, size_t size);

#endif