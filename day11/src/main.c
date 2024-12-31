/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:58:50 by abelov            #+#    #+#             */
/*   Updated: 2024/12/30 18:58:52 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "day11.h"
#include "aoc_2024.h"
#include <sysexits.h>
#include <stdio.h>

int	nbrlen(uint64_t nbr)
{
	int acc = 0;
	const unsigned int	radix = 10;

	while (nbr > 0)
	{
		nbr = nbr / radix;
		acc++;
	}
	return (acc);
}

uint64_t blink(uint64_t rock, int blinks, Node **cache)
{
	if (blinks == 0) return 1;

	Node *cached = get(*cache, (Point){.x = rock, .y = blinks});
	if (cached) return cached->val;

	int nblen = nbrlen(rock);
	uint64_t x = 0;

	if (rock == 0)
		x = blink(1, blinks - 1, cache);
	else if (nblen % 2 == 0)
	{
		char buf_left[20];
		char buf_right[20];
		snprintf(buf_left, 20,"%lu", rock);
		strcpy(buf_right, buf_left + nblen / 2);
		buf_left[nblen / 2] = '\0';

		uint64_t left = atoll(buf_left), right = atoll(buf_right);
		x = blink(left, blinks - 1, cache)
			+ blink(right, blinks - 1, cache);
	}
	else
		x = blink( rock * 2024, blinks - 1, cache);
	place(cache, (Point){.x = rock, .y = blinks}, x);
	return (x);
}

uint64_t part1(t_info *info)
{
	uint64_t acc = 0;
	Node *lut = NULL, *iter, *tmp;

	Array *arr = &info->input;

	arr->ss = 0;
	while (arr->ss < arr->size)
	{
		acc += blink(arr->arr[arr->ss], 25, &lut);
		arr->ss++;
	}

	HASH_ITER(hh, lut, iter, tmp)
	{
		HASH_DEL(lut, iter);
		free(iter);
	}

	return (acc);
}

uint64_t part2(t_info *info)
{
	uint64_t acc = 0;

	Node *lut = NULL, *iter, *tmp;

	Array *arr = &info->input;

	arr->ss = 0;
	while (arr->ss < arr->size)
	{
		acc += blink(arr->arr[arr->ss], 75, &lut);
		arr->ss++;
	}

	HASH_ITER(hh, lut, iter, tmp)
	{
		HASH_DEL(lut, iter);
		free(iter);
	}

	return (acc);
}

void prepare(t_info *info)
{
	char	*save_ptr;
	char 	strbuf[1024];

	static int starr[ARRAY_COUNT][ELEMENT_COUNT];

	Array *arr = &(Array){ .arr = starr[0], .ss = 0, .size = ELEMENT_COUNT};

	GList *input = read_file();
	char *input_str = strdup(g_list_nth(input, 0)->data);
	g_list_free_full(input, free);
	input = NULL;

	errno = 0;
	long val = strtol(input_str, &save_ptr, 10);
	if (!(errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) && !(errno != 0 && val == 0))
		arr->arr[arr->ss++] = (int) val;

	while (save_ptr && *save_ptr)
	{
		errno = 0;
		val = strtol(save_ptr, &save_ptr, 10);
		if (!(errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) && !(errno != 0 && val == 0))
			arr->arr[arr->ss++] = (int) val;
		else
		{
			snprintf(strbuf, 1024, "error parsing the line: %s", input_str);
			free(input_str);
			perror(strbuf);
			exit(EX_DATAERR);
		}
	}
	arr->size = arr->ss;
	arr->ss = 0;

	info->input = *arr;

	free(input_str);
}

int main(void)
{
	static t_info	info;
	prepare(&info);

	printf("part1: %lu\n=====================================\n", part1(&info));
	printf("part2: %lu\n", part2(&info));
	return (EX_OK);
}

