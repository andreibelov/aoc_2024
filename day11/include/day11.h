/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day11.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:59:42 by abelov            #+#    #+#             */
/*   Updated: 2024/12/30 18:59:43 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DAY11_H
#define DAY11_H

#include "aoc_2024_defs.h"
#include <uthash.h>
#include <stdbool.h>
#include <ctype.h>

#define ARRAY_COUNT 1
#define ELEMENT_COUNT 1024
#define STACK_MAX 16384

typedef struct s_info
{
	Array input;
}	t_info;

typedef struct he
{
	Point key;
	unsigned long long int val;
	UT_hash_handle hh;
}	Node;

typedef enum BlinkState
{
	PROCESS_START = 0,
	PROCESS_LEFT,
	PROCESS_RIGHT
}	BlinkState;

typedef struct
{
	uint64_t rock;
	int blinks;
	BlinkState state; // Tracks progress in the call
	uint64_t left, right; // Intermediate values
} StackFrame;

Node *get(Node *table, Point point);
Node *place(Node **table, Point point, unsigned long long int val);

#endif //DAY11_H
