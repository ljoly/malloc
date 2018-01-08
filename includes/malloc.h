/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 10:52:44 by ljoly             #+#    #+#             */
/*   Updated: 2018/01/08 18:52:36 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "libft.h"
# include <sys/mman.h>

# define TINY_SIZE 992
# define SMALL_SIZE 1000000000

typedef enum        e_type
{
	META,
    TINY,
    SMALL,
    LARGE,
	TINY_RANGE,
	SMALL_RANGE,
	LARGE_RANGE,
}                   t_type;

typedef struct      s_meta
{
	t_type			type;
	void			*ptr;
	int				size;
	int				size_left;
}                   t_meta;

#endif