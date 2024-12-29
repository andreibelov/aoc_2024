/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aoc_2024_defs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 22:49:44 by abelov            #+#    #+#             */
/*   Updated: 2024/12/10 22:49:49 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AOC_2024_DEFS_H
#define AOC_2024_DEFS_H

#include <stddef.h>

typedef struct StringArray
{
	char **arr;
	int size;
	int current;
}	StringArray;

typedef struct Array
{
	int *arr;
	int size;
	int ss;
}	Array;

typedef struct TwoDArray
{
	Array *arrays;
	int size;
	int curr;
}	TwoDArray;

typedef struct Point
{
	int x, y;
} Point;

typedef struct PointVal
{
	Point	coord;
	int 	val;
} PointVal;

typedef struct PointArray
{
	Point *arr;
	int size;
	int ss;
}	PointArray;

typedef struct PointArrayPooled
{
	Point *arr;
	int size;
	int ss;
	struct PointArrayPooled *_pool;
}	PointArrayPooled;

#endif //AOC_2024_DEFS_H
