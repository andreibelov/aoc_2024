/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 17:44:25 by abelov            #+#    #+#             */
/*   Updated: 2024/12/31 17:44:27 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sysexits.h>
#include <stdbool.h>
#include "day12.h"
#include "aoc_2024.h"

static const Point	view[4] = {
	{.x = 0, .y = -1}, // Up
	{.x = 0, .y =  1}, // Down
	{.x = -1, .y = 0}, // Left
	{.x = 1, .y =  0}  // Right
};

struct direction
{
	int Up;
	int Down;
	int Left;
	int Right;
} Direction = {
	.Up = Up,
	.Down = Down,
	.Left = Left,
	.Right = Right
};

void apply(gpointer data, gpointer user_data)
{
	StringArray *strings = user_data;
	strings->arr[strings->current++] = data;
//	printf("%s\n", (char *)data);
}

void prepare(t_info *info)
{
	GList *input = read_file();

	StringArray sa = {};
	sa.current = 0;
	sa.size = (int)g_list_length(input);
	sa.arr = (char **)malloc(sa.size * sizeof(char *));

	g_list_foreach(input, apply, &sa);
	g_list_free(input);
	input = NULL;

	sa.max.x = (int)strlen(sa.arr[0]);
	sa.max.y = sa.size;

	info->strings = sa;

	static Region static_data[ELEMENT_COUNT] = {};
	static Point static_data_p[ELEMENT_COUNT][ELEMENT_COUNT] = {};

	int k = -1;
	while(++k < ELEMENT_COUNT)
	{
		static_data[k].area = 0;
		static_data[k].perimiter = 0;
		static_data[k].points.ss = 0;
		static_data[k].points.size = ELEMENT_COUNT;
		int l = -1;
		while (++l < ELEMENT_COUNT)
			static_data[k].points.arr = &static_data_p[k][l];
	}
	info->regions = (RegionArray){.arr = static_data, .size = ELEMENT_COUNT, .ss = 0};

	static Point static_point_array[POINTARRAY_SIZE] = {};

	PointArray pa = {.arr = static_point_array, .size = POINTARRAY_SIZE, .ss = 0};

	int y = -1;
	while(++y < sa.max.y)
	{
		int x = -1;
		while (++x < info->strings.max.x)
			pa.arr[pa.ss++] = (Point) {x, y};
	}

	pa.size = pa.ss;
	pa.ss = 0;

	info->points = pa;


}

RegionArray *getRegions(t_info *info)
{
	StringArray *grid = &info->strings;
	PointArray *pa = &info->points;
	RegionArray *regions = &info->regions;

	Node *visited = NULL, *iter = NULL, *tmp = NULL;

	pa->ss = 0;
	while(pa->ss < pa->size)
	{
		Point p = pa->arr[pa->ss++];
		if (!get(visited, p))
		{
			char plant;
			if(!getGridVal(grid, p, &plant)) continue;
			int front = 0, rear = 0;  // Queue front and rear pointers
			Point queue[MAX_QUEUE_SIZE];  // Queue for breadth-first traversal

			Region *region = &regions->arr[regions->ss++];
			region->plant = plant;

			enqueue(queue, &rear, &front, p);
			while(front != rear)
			{
				Point vertex;
				dequeue(queue, &rear, &front, &vertex);
				if (!get(visited, vertex))
				{
					region->area++;
					char val;
					getGridVal(grid, vertex, &val);
					place(&visited, vertex, val);

					region->points.arr[region->points.ss++] = vertex;

					PointArrayPooled nb = getNeighbours(vertex);

					while(nb.ss < nb.size)
					{
						Point neighbour = nb.arr[nb.ss++];

						if (check_boundaries(neighbour, grid->max))
						{
							getGridVal(grid, neighbour, &val);
							if(val != region->plant)
								region->perimiter++;
							else if (!get(visited, neighbour))
								enqueue(queue, &rear, &front, neighbour);
						}
						else region->perimiter++;
					}
					returnPointArrayPooled(nb);
				}
			}
			region->points.size = region->points.ss;
			region->points.ss = 0;
		}
	}
	regions->size = regions->ss;
	regions->ss = 0;

	HASH_ITER(hh, visited, iter, tmp)
	{
		HASH_DEL(visited, iter);
		free(iter);
	}
	return (regions);
}

int inRegion(Region *region, Point p)
{
	int i = -1;
	while (++i < region->points.size)
		if (equ(region->points.arr[i], p)) return (true);
	return (false);
}

int edge_cmp(const Edge *a, const Edge *b)
{
	return (!(equ(a->in, b->in) && equ(a->out, b->out)));
}

int getSides(Region *region)
{
	PointArray pa = region->points;

	GList *perimeter = NULL;
	Node *visited = NULL, *iter = NULL, *tmp = NULL;

	pa.ss = 0;
	while (pa.ss < pa.size)
	{
		Point vertex =  pa.arr[pa.ss++];

		int i = -1;
		while(++i < 4)
		{
			Point next = add(vertex, view[Up + i]);

			if (get(visited, next)) continue;

			if (!inRegion(region, next))
			{
				Edge *edge = (Edge*) malloc(sizeof(Edge));
				*edge = (Edge) {vertex, next};
				perimeter = g_list_append(perimeter, edge);
			}
			else
			{
				place(&visited, next, region->plant);
			}
		}
	}

	GList *it = perimeter;
	unsigned int perimeter_size = g_list_length(perimeter);

	int redundant = 0;

	while(it)
	{
		Edge *eg = it->data;

		int i = -1;
		while (++i < 2)
		{
			Point dir = view[1 + (2 * i)];
			Edge new_edge = (Edge){ add(eg->in, dir), add(eg->out, dir)};
			GList *found = g_list_find_custom(perimeter, &new_edge, (GCompareFunc)edge_cmp);
			if (found) redundant++;
		}
		it = it->next;
	}
	HASH_ITER(hh, visited, iter, tmp)
	{
		HASH_DEL(visited, iter);
		free(iter);
	}

	g_list_free_full(perimeter, free);
	return (int)(perimeter_size - redundant);
}

int part1(t_info *info)
{
	int acc = 0;
	getRegions(info);

	info->regions.ss = 0;
	while(info->regions.ss < info->regions.size)
	{
		Region *region = &info->regions.arr[info->regions.ss++];
		acc += region->area * region->perimiter;
	}

	return (acc);
}

int part2(t_info *info)
{
	int acc = 0;

	info->regions.ss = 0;
	while(info->regions.ss < info->regions.size)
	{
		Region *region = &info->regions.arr[info->regions.ss++];
		acc += region->area * getSides(region);
	}

	return (acc);
}

int main(void)
{
	static t_info	info;
	prepare(&info);

	printf("part1: %d\n=====================================\n", part1(&info));
	printf("part2: %d\n", part2(&info));
	return (EX_OK);
}
