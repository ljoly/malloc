/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 10:52:44 by ljoly             #+#    #+#             */
/*   Updated: 2018/01/11 18:29:09 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "libft.h"
# include <sys/mman.h>

# define TINY_MAX_SIZE 992
# define SMALL_MAX_SIZE 1000000000

typedef enum        e_type
{
	META,
    TINY,
    SMALL,
    LARGE,
	TINY_RANGE,
	SMALL_RANGE,
	LARGE_RANGE
}                   t_type;

typedef struct      s_meta
{
	t_type			type;
	void			*ptr;
	int				size_left;
}                   t_meta;

extern t_meta   	*meta;

void				*ft_malloc(size_t size);
void 				*malloc(size_t size);
void 				*realloc(void *ptr, size_t size);

#endif