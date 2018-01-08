/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 18:09:38 by ljoly             #+#    #+#             */
/*   Updated: 2018/01/08 18:15:52 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int     main(void)
{
    char    *str;
    int     i;
    
    str = (char*)ft_malloc(sizeof(char) * 5);
    str[0] = '1';
    str[1] = '2';
    str[2] = '3';
    str[3] = '4';
    str[4] = '\0';
    ft_printf("%s\n", str);
    i = getpagesize();
    ft_printf("%d\n", i);
    return (0);
}