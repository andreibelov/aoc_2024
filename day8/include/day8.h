/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day8.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 18:55:03 by abelov            #+#    #+#             */
/*   Updated: 2024/12/25 18:55:03 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DAY8_H
#define DAY8_H

#include <glib.h>
#include <uthash.h>
typedef struct he
{
	Point key;
	UT_hash_handle hh;
}	Node;

typedef struct s_info
{
	PointArray **freq;
	int		size;
	Point 	max;
	int		ss;
}	t_info;

Point add(Point a, Point b);
Point sub(Point p, Point q);
Point mul(Point p, int mul);
int check_boundaries(Point point, Point max);
int manhattan(Point p, Point q);

Node *get(Node **table, Point point);
Node *place(Node **table, Point point);
GList *read_file();


#endif //DAY8_H
