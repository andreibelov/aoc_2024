/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:46:22 by abelov            #+#    #+#             */
/*   Updated: 2024/12/02 10:46:23 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "aoc_2024.h"
#include "day2.h"



int parse_input(GList **numbers_list);

int is_valid(Array *arr)
{
	int i = -1;
	long diff;
	int curr;
	int prev;

	int increasing = 0;

	prev = arr->arr[++i];
	curr = arr->arr[++i];

	diff = curr - prev;

	if (ABS(diff) > 3 || diff == 0)
		return (0);
	if (diff > 0)
	{
		increasing = 1;
		puts("increasing");
	}
	else
		puts("decreasing");
	printf("%d, %d : %ld\n", prev, curr, diff);
	prev = curr;

	while (++i < arr->size)
	{
		curr = arr->arr[i];
		diff = curr - prev;
		printf("%d, %d : %ld\n", prev, curr, diff);
		if ((ABS(diff) > 3) || diff == 0 || (diff < 0 && increasing) || (diff > 0 && !increasing))
			return (0);
		prev = curr;
	}

	return (1);
}

void print_tab(gpointer data, gpointer user_data)
{
	long *acc = user_data;

	Array *arr = data;
	ft_print_int_tab(arr->arr, arr->size, NULL);

	if (is_valid(arr))
	{
		puts("valid\n");
		(*acc)++;
	}
	else
		puts("invalid\n");
}

bool bad_diff(long diff, int increasing)
{ return (ABS(diff) > 3) || diff == 0 || (diff < 0 && increasing) || (diff > 0 && !increasing); }


int can_make_valid(Array *arr)
{
	int i, j;
	int retval = 0;
	Array to_test = {
		.arr = (int *)malloc(sizeof(int) * (arr->size - 1)),
		.size = arr->size - 1
	};

	i = -1;
	while (++i < (arr->size))
	{
		memcpy(to_test.arr, arr->arr, sizeof(int) * i);
		int *dest = to_test.arr + i;
		int *src = arr->arr + i + 1;
		int to_copy = (arr->size - i - 1);
		memcpy(dest, src, sizeof(int) * to_copy);

		ft_print_int_tab(to_test.arr, to_test.size, NULL);
		if (is_valid(&to_test))
		{
			retval = 1;
			break;
		}
	}
	free(arr->arr);
	free(to_test.arr);
	return (retval);
}

int is_valid_with_problem_dampener(Array *arr)
{
	bool safe = 0;

	if (is_valid(arr) || can_make_valid(arr))
		return (1);
	return (0);
}

void problem_dampener(gpointer data, gpointer user_data)
{
	long *acc = user_data;

	Array *arr = data;
	ft_print_int_tab(arr->arr, arr->size, NULL);

	if (is_valid_with_problem_dampener(arr))
	{
		puts("valid\n");
		(*acc)++;
	}
	else
		puts("invalid\n");
}

int part1(void)
{
	long acc = 0;
	GList *numbers_list;

	int listsize = parse_input(&numbers_list);
	g_list_foreach(numbers_list, print_tab, &acc);
	return ((int )acc);
}

int part2(void)
{
	long acc = 0;
	GList *numbers_list;

	int listsize = parse_input(&numbers_list);
	g_list_foreach(numbers_list, problem_dampener, &acc);
	return ((int )acc);
}

int main(void)
{
	printf("part1: %d\n\n=====================================\n\n", part1());
	printf("part2: %d\n", part2());
	return (EX_OK);
}


int parse_input(GList **numbers_list)
{
	int i;
	long nbr = 0;
	Array *arr;
	int *ints;

	int stack[MAX_LIST_SIZE];
	int stacksize = 0;

	int listsize = 0;

	char *lineptr = NULL;
	char *endptr = NULL;
	size_t n;
	ssize_t nread;

	FILE *f = fopen(INPUT_FILE_NAME, "r");

	while ((nread = getline(&lineptr, &n, f)) > 0)
	{
		errno = 0;
		nbr  = (int)strtol(lineptr, &endptr, 10);
		if (!(errno == ERANGE && (nbr == LONG_MAX || nbr == LONG_MIN)) && !(errno != 0 && nbr == 0))
			stack[stacksize++] = (int)nbr;
		while(*endptr && *endptr != '\n')
		{
			errno = 0;
			nbr  = (int)strtol(endptr, &endptr, 10);
			if (!(errno == ERANGE && (nbr == LONG_MAX || nbr == LONG_MIN)) && !(errno != 0 && nbr == 0))
				stack[stacksize++] = (int)nbr;
			else
				break;
		}

		arr = (Array *) malloc(sizeof(Array));
		*arr = (Array){ .size = stacksize, .arr = (int *) malloc(sizeof(int) * stacksize) };
		memcpy(arr->arr, stack, stacksize * sizeof(int));
		*numbers_list = g_list_append(*numbers_list, arr);
		stacksize = 0;
		*lineptr = '\0';
	}
	lineptr = (free(lineptr), NULL);
	fclose(f);
	return ((int)g_list_length(*numbers_list));
}
