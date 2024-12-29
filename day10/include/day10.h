/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day10.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 17:32:06 by abelov            #+#    #+#             */
/*   Updated: 2024/12/29 22:05:28 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DAY10_H
#define DAY10_H

#include "aoc_2024_defs.h"
#include <uthash.h>
#include <stdbool.h>
#include <ctype.h>

#define POINTARRAY_POOL_SIZE 16384

typedef enum Dir
{
	Up = 0,
	Down,
	Left,
	Right
}	Direction;

typedef struct Neighbours
{
	Point 	coord[4];
	int 	ss;
	int 	size;
}	Neighbours;

typedef struct s_info
{
	TwoDArray	grid;
	Point 		max;
	PointArrayPooled 	trails;
}	t_info;

Point add(Point a, Point b);
Point sub(Point p, Point q);
Point mul(Point p, int mul);

typedef struct he
{
	Point key;
	UT_hash_handle hh;
}	Node;

Node *place(Node **table, Point point);
Node *get(Node **table, Point point);

PointArrayPooled getNewPointArrayPooled(int size);
void returnPointArrayPooled(PointArrayPooled pa);

#endif //DAY10_H
