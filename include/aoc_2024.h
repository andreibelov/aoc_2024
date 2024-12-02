/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aoc_2024.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:11:08 by abelov            #+#    #+#             */
/*   Updated: 2024/12/02 12:11:10 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AOC_2024_H
#define AOC_2024_H

#include <sysexits.h>
#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>
#include <glib.h>

#define intcmp_f (__compar_fn_t) intcmp

int intcmp(const int *a, const int *b)
{ return (*a > *b) - (*a < *b); }

typedef struct Array
{
	int *arr;
	int size;
}	Array;

void ft_print_int_tab(int tab[], size_t size, const char *eol)
{
	size_t pos;

	pos = 0;
	printf("[");
	if (pos < size)
		printf("%d", tab[pos++]);
	while (pos < size)
		printf(", %d", tab[pos++]);
	printf("]%s", (!eol) ? "\n" : eol);
}


#endif //AOC_2024_H
