/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 18:09:38 by ljoly             #+#    #+#             */
/*   Updated: 2018/02/04 21:48:00 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int main(void)
{
    char *s1;
    char *s2;
    char *s3;

    s1 = (char *)ft_malloc(sizeof(char) * 7);
    s1[0] = 'h';
    s1[1] = 'e';
    s1[2] = 'l';
    s1[3] = 'l';
    s1[4] = 'o';
    s1[5] = '!';
    s1[6] = '\0';
    ft_printf("%s\n", s1);
    ft_printf("address s1 = %p\n", s1);    

    // ft_printf("\nON PRINT S1: \"%s\", ON PASSE A S2:\n\n", s1);

    s2 = (char *)ft_malloc(sizeof(char) * 5);
    s2[0] = '1';
    s2[1] = '2';
    s2[2] = '3';
    s2[3] = '4';
    s2[4] = '\0';
    ft_printf("%s\n", s2);
    ft_printf("address s2 = %p\n", s2);
    
    s3 = (char *)ft_malloc(sizeof(char) * 6);
    s3[0] = 's';
    s3[1] = 'a';
    s3[2] = 'l';
    s3[3] = 'u';
    s3[4] = 't';
    s3[5] = '\0';
    ft_printf("%s\n", s3);
    ft_printf("address s3 = %p\n", s3);
    
    ft_printf("\nmeta[2] = %s\n", meta[2].ptr);
    ft_printf("meta[3] = %s\n", meta[3].ptr);
    ft_printf("meta[4] = %s\n", meta[4].ptr);  
    return (0);
}