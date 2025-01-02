/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 18:51:19 by abelov            #+#    #+#             */
/*   Updated: 2024/12/31 18:51:20 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "day12.h"

int equ(Point a, Point b)
{
	return (a.x == b.x && a.y == b.y);
}

Point add(Point a, Point b)
{
	return (Point){.x = a.x + b.x, .y = a.y + b.y};
}

Point sub(Point p, Point q)
{
	return (Point){.x = p.x - q.x, .y = p.y - q.y};
}

Point mul(Point p, int mul)
{
	return (Point){.x = p.x * mul, .y = p.y * mul};
}

PointArrayPooled getNewPointArrayPooled(int size)
{
	static Point pool[POINTARRAY_POOL_SIZE];
	const int poolsize = POINTARRAY_POOL_SIZE;

	static PointArrayPooled	_pool = {
		.arr = pool,
		.size = poolsize,
		.ss = 0
	};

	PointArrayPooled pa = (PointArrayPooled){
		.arr = NULL, .size = 0, .ss = 0, ._pool = &_pool};

	if ((_pool.ss + size) < poolsize)
	{
		pa.arr = &pool[_pool.ss];
		pa.size = size;
		_pool.ss += size;
	}

	return pa;
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

void returnPointArrayPooled(PointArrayPooled pa)
{
	PointArrayPooled	*_pool = pa._pool;
	_pool->ss -= pa.size;
}

int check_boundaries(Point point, Point max)
{
	return ((point.x >= 0 && point.y >= 0) && (point.x < max.x && point.y < max.y));
}

int getGridVal(StringArray *grid, Point p, char *val)
{
	int retval = 0;

	if (check_boundaries(p, grid->max))
	{
		*val = *(grid->arr[p.y] + p.x);
		retval = 1;
	}
	return (retval);
}

int dequeue(Point *queue, const int *rear, int *front, Point *p)
{
	if(rear == front) return (-1);
	*p = queue[(*front)++];
	*front %= MAX_QUEUE_SIZE;
	return (0);
}

void enqueue(Point *queue, int *rear, const int *front,  Point el)
{
	if((*rear + 1) % MAX_QUEUE_SIZE == *front) return;
	queue[(*rear)++] = el;
	*rear %= MAX_QUEUE_SIZE;
}

Node *get(Node *table, Point point)
{
	Node *to_find = NULL;
	HASH_FIND(hh, table, &point, sizeof(Point), to_find);
	return (to_find);
}

Node *place(Node **table, Point point, int val)
{
	Node *new_node = get(*table, point);
	if (!new_node)
	{
		new_node = (Node *) malloc(sizeof(Node));
		if (!new_node) return (NULL);
		memset(new_node, 0, sizeof(Node));
		new_node->key = point;
		new_node->val = val;
		HASH_ADD(hh, *table, key, sizeof(Point), new_node);
	}
	return (new_node);
}

