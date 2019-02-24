/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 18:12:24 by ljoly             #+#    #+#             */
/*   Updated: 2019/02/24 16:46:25 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*calloc(size_t count, size_t size)
{
	char	*ptr;

	pthread_mutex_lock(mutex_sglton());
	pthread_mutex_unlock(mutex_sglton());
	ptr = malloc(count * size);
	pthread_mutex_lock(mutex_sglton());
	ft_bzero(ptr, count * size);
	pthread_mutex_unlock(mutex_sglton());
	return (ptr);
}
