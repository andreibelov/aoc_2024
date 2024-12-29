/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 21:40:28 by abelov            #+#    #+#             */
/*   Updated: 2024/12/29 21:40:29 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "day10.h"

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

void returnPointArrayPooled(PointArrayPooled pa)
{
	PointArrayPooled	*_pool = pa._pool;
	_pool->ss -= pa.size;
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

Node *get(Node **table, Point point)
{
	Node *to_find = NULL;
	HASH_FIND(hh, *table, &point, sizeof(Point), to_find);
	return (to_find);
}

Node *place(Node **table, Point point)
{
	Node *new_node = get(table, point);
	if (!new_node)
	{
		new_node = (Node *) malloc(sizeof(Node));
		if (!new_node) return (NULL);
		memset(new_node, 0, sizeof(Node));
		new_node->key = point;
		HASH_ADD(hh, *table, key, sizeof(Point), new_node);
	}
	return (new_node);
}