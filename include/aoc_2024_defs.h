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

typedef struct PointArray
{
	Point *arr;
	int size;
	int ss;
}	PointArray;

#endif //AOC_2024_DEFS_H
