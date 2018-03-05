/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 10:52:44 by ljoly             #+#    #+#             */
/*   Updated: 2018/03/05 18:29:09 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "libft.h"
# include <sys/mman.h>
# include <pthread.h>

/*
** Considering this program will only be used on 64-bit architectures
*/
# define TINY_QUANTUM 16
# define TINY_MAX 1024
# define T_REGION_SIZE 2048000

# define SMALL_QUANTUM 512
# define SMALL_MAX 128000
# define S_REGION_SIZE 16000000

# define MMAP_FLAGS PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE

/*
** Blocks are subzones of Regions. Meta is an array of meta data.
*/
typedef enum        e_type
{
/*0*/	NO_TYPE,
/*1*/	TINY_BLOCK,
/*2*/	SMALL_BLOCK,
/*3*/	TINY_FREED,
/*4*/	SMALL_FREED,
/*5*/	TINY_REGION,
/*6*/	SMALL_REGION,
/*7*/	LARGE_REGION,
/*8*/	LARGE_FREED,
}                   t_type;

typedef struct      s_meta
{
	t_type			type;
	char			*ptr;
	size_t			size;
}                   t_meta;

extern t_meta   	*g_meta;
pthread_mutex_t		g_mutex;

/*
** Specs of the requested zone
*/
typedef struct		s_req
{
	t_type			region;
	t_type			block;	
	size_t			region_size;
	size_t			size_to_map;
	size_t			index;
	char			*zone;
}					t_req;

void				free(void *ptr);
void 				*malloc(size_t size);
void 				*realloc(void *ptr, size_t size);

void            	allocate_meta(void);
void				map_zone(t_req *r, t_type type, t_bool new_block);
void				show_alloc_mem();

#endif