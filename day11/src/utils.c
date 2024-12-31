/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:03:53 by abelov            #+#    #+#             */
/*   Updated: 2024/12/30 20:03:55 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "day11.h"

Node *get(Node *table, Point point)
{
	Node *to_find = NULL;
	HASH_FIND(hh, table, &point, sizeof(Point), to_find);
	return (to_find);
}

Node *place(Node **table, Point point, unsigned long long int val)
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
