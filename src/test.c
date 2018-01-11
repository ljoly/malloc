/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 18:09:38 by ljoly             #+#    #+#             */
/*   Updated: 2018/01/11 18:20:28 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int main(void)
{
    char *s1;
    char *s2;
    char *s3;

    ft_printf("sizeof t_meta: %d\n", sizeof(t_meta));
    s1 = (char *)ft_malloc(sizeof(char) * 5);
    s1[0] = '1';
    s1[1] = '2';
    s1[2] = '3';
    s1[3] = '4';
    s1[4] = '\0';
    ft_printf("%s\n", s1);

    s2 = (char *)ft_malloc(sizeof(char) * 6);
    s2[0] = 'h';
    s2[1] = 'e';
    s2[2] = 'l';
    s2[3] = 'l';
    s2[4] = 'o';
    s2[5] = '\0';
    ft_printf("%s\n", s2);

    s3 = (char *)ft_malloc(sizeof(char) * 6);
    s3[0] = 's';
    s3[1] = 'a';
    s3[2] = 'l';
    s3[3] = 'u';
    s3[4] = 't';
    s3[5] = '\0';
    ft_printf("%s\n", s3);

    return (0);
}