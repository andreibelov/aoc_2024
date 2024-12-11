/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:14:32 by abelov            #+#    #+#             */
/*   Updated: 2024/12/06 13:14:33 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sysexits.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "aoc_2024.h"
#include "day6.h"

Direction d = Up;
Point curr, start;
Point view[4] = {
	{.x = 0, .y =  -1},  // Up
	{.x = 0, .y =  1},   // Down
	{.x = -1, .y = 0},  // Left
	{.x = 1, .y =  0}    // Right
};

Node *grid = NULL, *seen = NULL, *possible = NULL, *loop_tbl = NULL;

void prepare();

Point next(Point pos, int *ok, int *looped)
{
	Node *visited = get(&loop_tbl, pos);
	if (visited && visited->dir == d) *looped = true;
	else
	{
		if (!visited)
		{
			visited = place(&loop_tbl, pos);
			visited->dir = d;
		}

		Node *entry = get(&grid, add(pos, view[d]));

		if (!entry) *ok = false;
		else if (entry->value == '#') d = rotate(d);
		else
		{
			pos = add(pos, view[d]);

			place(&seen, pos)->value = true;
			place(&possible, pos)->value = true;

			if ((pos.x == start.x && pos.y == start.y) && d == Up)
				*looped = true;
		}
	}
	return pos;
}

bool hasloop(Point obstacle)
{
	int ok = true;
	int looped = false;

	Node *found = get(&grid, obstacle);

	if (found && found->value == '.')
	{

		found->value = '#';

		clear(&seen);
		clear(&loop_tbl);

		curr = start;
		d = Up;

		while (ok && !looped)
			curr = next(curr, &ok, &looped);

		found->value = '.';
	}
	return (looped);
}

int part1()
{
	int ok = true;
	int looped = false;

	curr = start;
	place(&seen, curr)->value = true;
	while (ok)
		curr = next(curr, &ok, &looped);
	return ((int)HASH_COUNT(seen));
}

int part2()
{
	int count = 0;
	Node *iter = NULL, *tmp = NULL;

	Point points[10000];
	int ss = 0;

	HASH_ITER(hh, possible, iter, tmp) points[ss++] = iter->key;

	while(ss)
	{
		if (hasloop(points[--ss]))
			count++;
	}
	return (count);
}

int main(void)
{
	prepare();
	printf("part1: %d\n=====================================\n", part1());
	printf("part2: %d\n", part2());
	return (EX_OK);
}

void prepare()
{
	StringArray strings;

	GList *input = read_file();

	strings.current = 0;
	strings.size = (int)g_list_length(input);
	strings.arr = (char **)malloc(strings.size * sizeof(char *));

	g_list_foreach(input, apply, &strings);
	g_list_free(input);
	input = NULL;

	strings.current = 0;
	while (strings.current < strings.size)
	{
		char *str = strings.arr[strings.current];
		char *ptr = str;
		while(*str)
		{
			Point p = {.x= (int)(str - ptr), .y = strings.current};
			place(&grid, p)->value = *str;
			if (*str == '^')
				start = p;
			str++;
		}
		free(ptr);
		strings.current++;
	}
	free(strings.arr);

	size_t grid_size = HASH_COUNT(grid);
	printf("grid size: '%lu'\n", grid_size);
	printf("=====================================\n");
}

