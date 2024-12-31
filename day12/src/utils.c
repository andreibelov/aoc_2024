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

Node *get(Node *table, Point point)
{
	Node *to_find = NULL;
	HASH_FIND(hh, table, &point, sizeof(Point), to_find);
	return (to_find);
}

Node *place(Node **table, Point point, Direction dir)
{
	Node *new_node = get(*table, point);
	if (!new_node)
	{
		new_node = (Node *) malloc(sizeof(Node));
		if (!new_node) return (NULL);
		memset(new_node, 0, sizeof(Node));
		new_node->key = point;
		new_node->dir = dir;
		HASH_ADD(hh, *table, key, sizeof(Point), new_node);
	}
	return (new_node);
}

