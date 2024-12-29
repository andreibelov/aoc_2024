/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 17:24:30 by abelov            #+#    #+#             */
/*   Updated: 2024/12/29 17:24:31 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sysexits.h>
#include "day10.h"
#include <aoc_2024.h>

#define ARRAY_COUNT 100
#define POINTS_COUNT 1024
#define ELEMENT_COUNT 100
#define MAX_QUEUE_SIZE 1024

void apply(gpointer data, gpointer user_data)
{
	char c;
	char *str = data;
	char *const ptr = data;
	t_info *info = user_data;

	PointArrayPooled *pa = &info->trails;

	Array *arr = &info->grid.arrays[info->max.y];

	arr->ss = 0;
	while (*str)
	{
		c = *str;
		if (isdigit(c))
		{
			arr->arr[arr->ss++] = c - '0';
			if (c == '0')
				pa->arr[pa->ss++] = (Point){
					.x = (int)(str - ptr), .y = info->max.y };
		}
		str++;
	}
	arr->size = arr->ss;
	arr->ss = 0;

	ft_println_int_array(arr);

	info->max.x = MAX(info->max.x, (int)(str - ptr));
	info->max.y++;
	free(ptr);
}

void prepare(t_info *info)
{
	static Point points[POINTS_COUNT];
	static Array paz[ARRAY_COUNT] = {};
	static int static_data[ARRAY_COUNT][ELEMENT_COUNT] = {};

	info->max = (Point){.x = 0, .y = 0};
	info->grid.size = ARRAY_COUNT;
	info->grid.arrays = paz;
	info->trails.arr = points;
	info->trails.size = POINTS_COUNT;
	info->trails.ss = 0;

	int i = -1;
	while (++i < ARRAY_COUNT)
	{
		paz[i].arr = static_data[i];
		paz[i].ss = 0;
		paz[i].size = ELEMENT_COUNT;
	}

	GList *input = read_file();
	g_list_foreach(input, apply, info);
	g_list_free(input);

	info->trails.size = info->trails.ss;
	info->trails.ss = 0;
}

int getGridVal(TwoDArray *grid, Point p, int *val)
{
	int retval = 0;

	Point max = { .x = grid->arrays[0].size, .y = grid->size};

	if ((p.x >= 0 && p.y >= 0) && (p.x < max.x && p.y < max.y))
	{
		*val = grid->arrays[p.y].arr[p.x];
		retval = 1;
	}
	return (retval);
}

PointArrayPooled getNeighbours(Point p)
{
	static const Point	view[4] = {
		{.x = 0, .y = -1}, // Up
		{.x = 0, .y =  1}, // Down
		{.x = -1, .y = 0}, // Left
		{.x = 1, .y =  0}  // Right
	};

	int i = -1;
	PointArrayPooled nb = getNewPointArrayPooled(4);
	while (++i < 4)
		nb.arr[Up + i] = add(p, view[Up + i]);
	return (nb);
}

int	findPaths(t_info *info, Point start)
{
	Node *paths = NULL, *iter, *tmp;

	int val, acc = 0;
	int front = 0, rear = 0;  // Queue front and rear pointers
	Point p;
	PointVal current;
	PointVal queue[MAX_QUEUE_SIZE];  // Queue for breadth-first traversal
	PointArrayPooled nb;

	queue[rear++] = (PointVal){ start, 0};
	while(front != rear)
	{
		current = queue[front++];  // Dequeue the front element
		if (current.val == 9)
			place(&paths, current.coord);
		else
		{
			nb = getNeighbours(current.coord);
			while(nb.ss < nb.size)
			{
				int next = current.val + 1;
				p = nb.arr[nb.ss++];
				if (getGridVal(&info->grid, p, &val) && val == next)
					queue[rear++] = (PointVal){ p, next};
			}
			returnPointArrayPooled(nb);
		}
	}

	HASH_ITER(hh, paths, iter, tmp)
	{
		acc++;
		HASH_DEL(paths, iter);
		free(iter);
	}
	return (acc);
}

int	findAllPaths(t_info *info, Point start)
{
	int val, paths = 0;
	int front = 0, rear = 0;  // Queue front and rear pointers
	Point p;
	PointVal current;
	PointVal queue[MAX_QUEUE_SIZE];  // Queue for breadth-first traversal
	PointArrayPooled nb;

	queue[rear++] = (PointVal){ start, 0};

	while(front != rear)
	{
		current = queue[front++];  // Dequeue the front element
		if (current.val == 9)
			paths++;
		else
		{
			nb = getNeighbours(current.coord);
			while(nb.ss < nb.size)
			{
				int next = current.val + 1;
				p = nb.arr[nb.ss++];
				if (getGridVal(&info->grid, p, &val) && val == next)
					queue[rear++] = (PointVal){ p, next};
			}
			returnPointArrayPooled(nb);
		}
	}
	return (paths);
}

int part1(t_info *info)
{
	long acc = 0;

	while (info->trails.ss < info->trails.size)
		acc += findPaths(info, info->trails.arr[info->trails.ss++]);

	info->trails.ss = 0;

	return ((int)acc);
}

int part2(t_info *info)
{
	long acc = 0;

	while (info->trails.ss < info->trails.size)
		acc += findAllPaths(info, info->trails.arr[info->trails.ss++]);

	return ((int)acc);
}

int main(void)
{
	static t_info	info;
	prepare(&info);

	printf("part1: %d\n=====================================\n", part1(&info));
	printf("part2: %d\n", part2(&info));
	return (EX_OK);
}
