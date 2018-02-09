/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 18:09:38 by ljoly             #+#    #+#             */
/*   Updated: 2018/02/09 19:43:59 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int main(void)
{
    char *s0;
    char *s1;
    char *s2;
    char *s3;
    char *s4;
    char *sm1;
    char *sm2;
    char *L1;
    char *L2;
    char *s5;

    // TINY

    s0 = (char *)ft_malloc(sizeof(char) * 0);
    s0[0] = 's';
    s0[1] = '0';
    ft_printf("%s\n", s0);
    ft_printf("address s0 = %p\n", s0);

    s1 = (char *)ft_malloc(sizeof(char) * 7);
    s1[0] = 's';
    s1[1] = '1';
    ft_printf("%s\n", s1);
    ft_printf("address s1 = %p\n", s1);

    s2 = (char *)ft_malloc(sizeof(char) * 5);
    s2[0] = 's';
    s2[1] = '2';
    ft_printf("%s\n", s2);
    ft_printf("address s2 = %p\n", s2);

    s3 = (char *)ft_malloc(sizeof(char) * 40);
    s3[0] = 's';
    s3[1] = '3';
    ft_printf("%s\n", s3);
    ft_printf("address s3 = %p\n", s3);

    s4 = (char *)ft_malloc(sizeof(char) * 3);
    s4[0] = 's';
    s4[1] = '4';
    ft_printf("%s\n", s4);
    ft_printf("address s4 = %p\n", s4);

    // SMALL

    sm1 = (char *)ft_malloc(sizeof(char) * 993);
    sm1[0] = 'S';
    sm1[1] = 'M';
    sm1[2] = '1';
    sm1[3] = '\0';

    sm2 = (char *)ft_malloc(sizeof(char) * 126991);
    sm2[0] = 'S';
    sm2[1] = 'M';
    sm2[2] = '2';
    sm2[3] = '\0';

    // LARGE

    L1 = (char *)ft_malloc(sizeof(char) * 1000000);
    L1[0] = 'L';
    L1[1] = '1';
    L1[2] = '\0';

    L2 = (char *)ft_malloc(sizeof(char) * 16000000);
    L2[0] = 'L';
    L2[1] = '2';
    L2[2] = '\0';

    // ANOTHER TINY

    s5 = (char *)ft_malloc(sizeof(char) * 447);
    s5[0] = 's';
    s5[1] = '5';

    ft_printf("\naddress s0 = %p\n", s0);
    ft_printf("address s1 = %p\n", s1);
    ft_printf("address s2 = %p\n", s2);
    ft_printf("address s3 = %p\n", s3);
    ft_printf("address s4 = %p\n", s4);
    ft_printf("address sm1 = %p\n", sm1);
    ft_printf("address sm2 = %p\n", sm2);
    ft_printf("address L1 = %p\n", L1);
    ft_printf("address L2 = %p\n", L2);
    ft_printf("address s5 = %p\n", s5);
    

    size_t i;

    i = 2;
    while (i < meta[0].type - meta[0].size)
    {
        ft_printf("meta[%d] = %s\n", i, meta[i].ptr);
        i++;
    }
    return (0);
}
