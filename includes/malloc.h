/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 10:52:44 by ljoly             #+#    #+#             */
/*   Updated: 2018/01/29 19:09:35 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "libft.h"
# include <sys/mman.h>

/*
** Considering this program will only be used on 64-bit architectures
*/
# define TINY_QUANTUM 16
# define TINY_MAX 992
# define T_REGION_SIZE 2048000

# define SMALL_QUANTUM 512
# define SMALL_MAX 126992
# define S_REGION_SIZE 16000000

# define MMAP_FLAGS PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE

/*
** Blocks are subzones of Regions. Meta is an array of meta data.
*/
typedef enum        e_type
{
	META,
    TINY_BLOCK,
    SMALL_BLOCK,
    LARGE_BLOCK,
	TINY_REGION,
	SMALL_REGION,
	LARGE_REGION
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