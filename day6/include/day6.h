/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day6.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 14:12:55 by abelov            #+#    #+#             */
/*   Updated: 2024/12/06 14:12:55 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DAY6_H
#define DAY6_H

typedef enum Dir
{
	Up = 0,
	Down,
	Left,
	Right
} Direction;

#include <uthash.h>
typedef struct he
{
	Point key;
	union {
		char value;
		Direction dir;
	};
	UT_hash_handle hh;
}	Node;

GList *read_file();
Node *get(Node **table, Point point);
Node *place(Node **table, Point point);
void apply(gpointer data, gpointer user_data);
Point add(Point a, Point b);
void clear(Node **table);
Direction rotate(Direction dir);

#endif //DAY6_H
