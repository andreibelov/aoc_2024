/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 00:54:09 by abelov            #+#    #+#             */
/*   Updated: 2024/12/28 00:54:10 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <glib.h>
#include "aoc_2024_defs.h"
#include "day8.h"

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

int check_boundaries(Point point, Point max)
{
	return ((point.x >= 0 && point.y >= 0) && (point.x < max.x && point.y < max.y));
}

int manhattan(Point p, Point q)
{
	return abs(p.x - q.x) + abs(p.y - q.y);
}
