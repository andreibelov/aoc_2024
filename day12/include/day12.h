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

#define ELEMENT_COUNT 1024
#define STACK_MAX 16384
#define MAX_QUEUE_SIZE 1024
#define POINTARRAY_SIZE 32768
#define POINTARRAY_POOL_SIZE 1024

typedef enum Dir
{
	Up = 0,
	Down,
	Left,
	Right
} Dir;

typedef struct he
{
	Point key;
	int val;
	UT_hash_handle hh;
}	Node;

typedef struct Region
{
	int area;
	int perimiter;
	char plant;
	PointArray points;
}	Region;

typedef struct RegionArray
{
	Region *arr;
	int ss;
	int size;
}	RegionArray;

typedef struct s_info
{
	StringArray strings;
	PointArray points;
	RegionArray regions;
}	t_info;

typedef struct Edge
{
	Point in;
	Point out;
}	Edge;

int equ(Point a, Point b);
Point add(Point a, Point b);
Point sub(Point p, Point q);
Point mul(Point p, int mul);
Node *place(Node **table, Point point, int val);
Node *get(Node *table, Point point);
int check_boundaries(Point point, Point max);
int getGridVal(StringArray *grid, Point p, char *val);
PointArrayPooled getNeighbours(Point p);
void returnPointArrayPooled(PointArrayPooled pa);
void enqueue(Point *queue, int *rear, const int *front,  Point el);
int dequeue(Point *queue, const int *rear, int *front, Point *p);

#endif //DAY12_H
