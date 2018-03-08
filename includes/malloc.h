/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 10:52:44 by ljoly             #+#    #+#             */
/*   Updated: 2018/03/08 16:22:43 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "../libft/includes/libft.h"
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
	size_t			size_request;	
	size_t			index;
	char			*zone;
}					t_req;

typedef struct		s_show_mem
{
	t_type			region;
	size_t			region_size;
	char			*region_ptr;
}					t_show_mem;

typedef struct		s_show_blocks
{
	char			*start;
	char			*end;
	size_t			size;
}					t_show_blocks;

void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);

void				init_request(t_req *r, size_t size);
void				allocate_meta(void);
void				map_zone(t_req *r, t_type type, t_bool new_block);

void				show_alloc_mem();
void				get_region_size(size_t size, t_show_mem *mem);
t_bool				is_block(t_type type);
t_bool				is_in_region(t_show_mem mem, char *ptr);
t_bool				is_large(t_type type);
void				print_region(t_show_mem mem);

#endif
