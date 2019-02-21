/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_multithreading.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 15:24:03 by ljoly             #+#    #+#             */
/*   Updated: 2019/02/21 15:24:25 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

pthread_mutex_t        *mutex_sglton(void)
{
	static pthread_mutex_t    mutex = PTHREAD_MUTEX_INITIALIZER;

	return (&mutex);
}
