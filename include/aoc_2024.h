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

#include "aoc_2024_defs.h"

#define intcmp_f (__compar_fn_t) intcmp

int intcmp(const int *a, const int *b)
{ return (*a > *b) - (*a < *b); }

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

void ft_print_str_tab(char **tab,  size_t size, const char *separator)
{
	size_t pos;
	const char *sep = " ";

	if (separator)
		sep = separator;

	pos = 0;
	printf("[");
	if (pos < size)
		printf("\"%s\"", tab[pos++]);
	while (pos < size)
		printf(",%s\"%s\"", sep, tab[pos++]);
	puts("]");
}

#endif //AOC_2024_H
