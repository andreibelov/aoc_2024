/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 22:26:38 by abelov            #+#    #+#             */
/*   Updated: 2024/12/10 22:26:38 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glib.h>
#include <stdio.h>
#include "aoc_2024_defs.h"
#include "day6.h"

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

void apply(gpointer data, gpointer user_data)
{
	StringArray *strings = user_data;
	strings->arr[strings->current++] = data;
}

Point add(Point a, Point b)
{
	return (Point){.x = a.x + b.x, .y = a.y + b.y};
}

void clear(Node **table)
{
	Node *iter, *tmp;
	HASH_ITER(hh, *table, iter, tmp)
	{
		HASH_DEL(*table, iter);
		free(iter);
	}
	*table = NULL;
}

Direction rotate(Direction dir)
{
	switch (dir) {
		case Up: return Right;
		case Down: return Left;
		case Left: return Up;
		case Right: return Down;
	}
	return Up; // Default case (should never happen)
}
