/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 10:52:44 by ljoly             #+#    #+#             */
/*   Updated: 2019/02/24 16:37:07 by ljoly            ###   ########.fr       */
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
# define SMALL_MAX 131072
# define S_REGION_SIZE 16121856

# define MMAP_FLAGS PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE

/*
** Blocks are subzones of Regions. Meta is an array of meta data.
*/
typedef enum		e_type
{
	NO_TYPE,
	TINY_BLOCK,
	SMALL_BLOCK,
	TINY_FREED,
	SMALL_FREED,
	TINY_REGION,
	SMALL_REGION,
	LARGE_REGION,
	LARGE_FREED,
}					t_type;

typedef struct		s_meta
{
	t_type			type;
	char			*ptr;
	size_t			size;
	size_t			size_request;
}					t_meta;

t_meta				*g_meta;

/*
** Specs of the requested zone
*/
typedef struct		s_req
{
	t_type			region;
	t_type			block;
	size_t			region_size_total;
	size_t			region_size_used;
	size_t			region_index;
	char			*region_ptr;
	size_t			size_to_map;
	size_t			size_request;
	size_t			block_index;
	void			*block_ptr;
}					t_req;

/*
** Print memory: regions
*/
typedef struct		s_show_mem
{
	t_type			region;
	size_t			region_size;
	char			*region_ptr;
}					t_show_mem;

/*
** Print memory: blocks
*/
typedef struct		s_show_blocks
{
	char			*start;
	char			*end;
	size_t			size;
}					t_show_blocks;

void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				*calloc(size_t count, size_t size);

void				init_request(t_req *r, size_t size);
void				allocate_meta(void);
void				map_zone(t_req *r, t_type type, t_bool new_block);

void				show_alloc_mem();
void				get_region_size(size_t size, t_show_mem *mem);
t_bool				is_block(t_type type);
t_bool				is_in_region(char *region_ptr, long region_size, char *ptr);
t_bool				is_large(t_type type);
void				print_region(t_show_mem mem);

pthread_mutex_t		*mutex_sglton(void);

#endif
