/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day12.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 18:03:22 by abelov            #+#    #+#             */
/*   Updated: 2024/12/31 18:03:23 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DAY12_H
#define DAY12_H

#include "aoc_2024_defs.h"
#include <uthash.h>

typedef enum Dir
{
	Up = 0,
	Down,
	Left,
	Right
} Direction;

typedef struct he
{
	Point key;
	Direction dir;
	UT_hash_handle hh;
}	Node;

typedef struct s_info
{
	StringArray strings;
}	t_info;

Node *place(Node **table, Point point, Direction dir);
Node *get(Node *table, Point point);

#endif //DAY12_H
