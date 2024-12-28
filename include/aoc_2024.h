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

void ft_println_int_array(Array arr)
{
	ft_print_int_tab(arr.arr, arr.size, "\n");
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

GList *read_file()
{
	char *lineptr = NULL;
	GList *input = NULL;
	size_t n;
	ssize_t nread;
	char buf[1024];

	FILE *f = fopen(INPUT_FILE_NAME, "r");
	if (!f)
	{
		snprintf(buf, 1024, "error opening file %s", INPUT_FILE_NAME);
		perror(buf);
		exit(EX_IOERR);
	}
	while ((nread = getline(&lineptr, &n, f)) > 0)
	{
		lineptr[nread - 1] = '\0';
		input = g_list_append(input, strdup(lineptr));
		*lineptr = '\0';
	}
	lineptr = (free(lineptr), NULL);
	fclose(f);
	return (input);
}


#endif //AOC_2024_H
