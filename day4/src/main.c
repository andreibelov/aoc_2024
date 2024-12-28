/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:32:10 by abelov            #+#    #+#             */
/*   Updated: 2024/12/04 14:32:10 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sysexits.h>
#include <stddef.h>
#include <glib.h>
#include <stdio.h>
#include <stdbool.h>
#include "aoc_2024.h"

#define MAX_STACK_SIZE 100024

GList *read_file();

void apply(gpointer data, gpointer user_data)
{
	StringArray *strings = user_data;
	strings->arr[strings->current++] = data;
}

int part1()
{
	long acc = 0;

	StringArray strings;

	GList *input = read_file();
	int xs = 0;
	Point xzs[MAX_STACK_SIZE];

	strings.current = 0;
	strings.size = (int)g_list_length(input);
	strings.arr = (char **)malloc(strings.size * sizeof(char *));
	g_list_foreach(input, apply, &strings);
	g_list_free(input);
	input = NULL;

	ft_print_str_tab(strings.arr, strings.size, "\n");

	strings.current = 0;
	while (strings.current < strings.size)
	{
		char *str = strings.arr[strings.current];
		char *ptr = str;
		while(*str)
		{
			if (*str == 'X')
				xzs[xs++] = (Point){.x = strings.current, .y = (int)(str - ptr)};
			str++;
		}
		strings.current++;
	}

	int string_size = (int)strlen(strings.arr[0]);

	while(xs)
	{
		char buff[5];
		Point X = xzs[--xs];

		bool cond1 = X.y < string_size - 3;
		bool cond2 = X.x < strings.size - 3;
		bool cond3 = X.x > 2;
		bool cond4 = (X.y > 2) && string_size > 3;

		if (cond1)
		{
			memset(buff, 0, 5);

			int i = -1;
			while (++i < 4)
			{
				char c = *(strings.arr[X.x] + X.y + i);
				buff[i] = c;
			}
			if (!strncmp("XMAS", buff, 4))
			{
				acc++;
				printf("X(%d,%d): %.*s\n", X.x, X.y, 4, buff);
			}
		}
		if (cond2)
		{
			memset(buff, 0, 5);

			int i = -1;
			while (++i < 4)
				buff[i] = *(strings.arr[X.x + i] + X.y);
			if (!strncmp("XMAS", buff, 4))
			{
				acc++;
				printf("X(%d,%d): %.*s\n", X.x, X.y, 4, buff);
			}

		}
		if (cond1 && cond2)
		{
			memset(buff, 0, 5);

			int i = -1;
			while (++i < 4)
			{
				char c = *(strings.arr[X.x + i] + X.y + i);
				buff[i] = c;
			}
			if (!strncmp("XMAS", buff, 4))
			{
				acc++;
				printf("X(%d,%d): %.*s\n", X.x, X.y, 4, buff);
			}
		}
		if (cond3)
		{
			memset(buff, 0, 5);

			int i = -1;
			while (++i < 4)
			{
				char c = *(strings.arr[X.x - i] + X.y);
				buff[i] = c;
			}
			if (!strncmp("XMAS", buff, 4))
			{
				acc++;
				printf("X(%d,%d): %.*s\n", X.x, X.y, 4, buff);
			}
		}
		if (cond1 && cond3)
		{
			memset(buff, 0, 5);

			int i = -1;
			while (++i < 4)
			{
				char c = *(strings.arr[X.x - i] + X.y + i);
				buff[i] = c;
			}
			if (!strncmp("XMAS", buff, 4))
			{
				acc++;
				printf("X(%d,%d): %.*s\n", X.x, X.y, 4, buff);
			}
		}
		if (cond4)
		{
			memset(buff, 0, 5);

			int i = -1;
			while (++i < 4)
			{
				char c = *(strings.arr[X.x] + X.y - i);
				buff[i] = c;
			}
			if (!strncmp("XMAS", buff, 4))
			{
				acc++;
				printf("X(%d,%d): %.*s\n", X.x, X.y, 4, buff);
			}
		}
		if (cond3 && cond4)
		{
			memset(buff, 0, 5);

			int i = -1;
			while (++i < 4)
			{
				char c = *(strings.arr[X.x - i] + X.y - i);
				buff[i] = c;
			}
			if (!strncmp("XMAS", buff, 4))
			{
				acc++;
				printf("X(%d,%d): %.*s\n", X.x, X.y, 4, buff);
			}
		}
		if (cond2 && cond4)
		{
			memset(buff, 0, 5);

			int i = -1;
			while (++i < 4)
			{
				char c = *(strings.arr[X.x + i] + X.y - i);
				buff[i] = c;
			}
			if (!strncmp("XMAS", buff, 4))
			{
				acc++;
				printf("X(%d,%d): %.*s\n", X.x, X.y, 4, buff);
			}
		}
	}

	strings.current = 0;
	while (strings.current < strings.size)
		free(strings.arr[strings.current++]);
	free(strings.arr);
	strings.size = 0;

	return ((int)acc);
}

int part2()
{
	long acc = 0;

	StringArray strings;

	GList *input = read_file();

	strings.current = 0;
	strings.size = (int)g_list_length(input);
	strings.arr = (char **)malloc(strings.size * sizeof(char *));
	g_list_foreach(input, apply, &strings);
	g_list_free(input);
	input = NULL;

	ft_print_str_tab(strings.arr, strings.size, "\n");

	Point curr = (Point){.x = 2, .y = 2};
	int string_size = (int)strlen(strings.arr[0]);

	while((curr.x < string_size) && (curr.y < strings.size))
	{
		char buff1[4];
		char buff2[4];

		buff1[3] = '\0';
		buff2[3] = '\0';

		int i = -1;
		while (++i < 3)
		{
			char c = *(strings.arr[curr.y - i] + curr.x - i);
			buff1[i] = c;
		}
		i = -1;
		while (++i < 3)
		{
			char c = *(strings.arr[curr.y - i] + (curr.x - 2) + i);
			buff2[i] = c;
		}
		if ((!strncmp("MAS", buff1, 3) || (!strncmp("SAM", buff1, 3))) &&
			(!strncmp("MAS", buff2, 3) || (!strncmp("SAM", buff2, 3))))
			acc++;

		curr.x++;
		if (curr.x >= string_size)
		{
			curr.x = 2;
			curr.y++;
		}
	}

	strings.current = 0;
	while (strings.current < strings.size)
		free(strings.arr[strings.current++]);
	free(strings.arr);
	strings.size = 0;
	return ((int)acc);
}

int main(void)
{
	printf("part1: %d\n\n=====================================\n\n", part1());
	printf("part2: %d\n", part2());
	return (EX_OK);
}
