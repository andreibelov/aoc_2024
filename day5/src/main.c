/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 23:37:14 by abelov            #+#    #+#             */
/*   Updated: 2024/12/11 17:23:13 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sysexits.h>
#include <glib.h>
#include <stdio.h>
#include <stdbool.h>
#include "aoc_2024.h"
#include "day5.h"

GList *read_file();

typedef enum states
{
	rules = 0,
	updates
} t_state;

typedef struct info
{
	t_state state;
	PointArray 	rules;
	TwoDArray 	updates;
	Node		**order;
} t_info;

Node *get(Node **table, int key)
{
	Node *to_find = NULL;
	HASH_FIND(hh, *table, &key, sizeof(int), to_find);
	return (to_find);
}

Node *place(Node **table, Point point)
{
	Node *new_node = get(table, point.x);
	if (!new_node)
	{
		new_node = (Node *) malloc(sizeof(Node));
		if (!new_node) return (NULL);
		memset(new_node, 0, sizeof(Node));
		HASH_ADD(hh, *table, key, sizeof(int), new_node);
	}
	new_node->key = point.x;
	new_node->idx = point.y;
	return (new_node);
}

void clear(Node **table)
{
	Node *iter, *tmp;
	HASH_ITER(hh, *table, iter, tmp)
	{
		HASH_DEL(*table, iter);
		free(iter);
	}
	*table = NULL;
}

void append_rules(char *lineptr, t_info *info)
{
	long val1, val2;
	char *endptr = NULL;

	errno = 0;
	val1  = (int)strtol(lineptr, &endptr, 10);
	if ((errno == ERANGE && (val1 == LONG_MAX || val1 == LONG_MIN))
		|| (errno != 0 && val1 == 0)) {
		perror("strtol");
		return;
	}

	endptr = strchr(lineptr, '|');
	if (!endptr++)
		return;

	errno = 0;
	val2  = (int)strtol(endptr, &endptr, 10);
	if ((errno == ERANGE && (val2 == LONG_MAX || val2 == LONG_MIN))
		|| (errno != 0 && val2 == 0)) {
		perror("strtol");
		return;
	}

	PointArray *pa = &info->rules;
	Point *p = &(Point){.x = (int)val1, .y = (int)val2};
	pa->arr[pa->ss++] = *p;
}

void place_static(NodeArray *np, Node **order, Point p)
{
	Node *new_node = &np->arr[np->ss++];
	memset(new_node, 0, sizeof(Node));
	new_node->key = p.x;
	new_node->idx = p.y;
	HASH_ADD(hh, *order, key, sizeof(int), new_node);
}

void append_updates(char *str, t_info *info)
{
	char		*save_ptr;
	static Node	pool[1024];

	static NodeArray np = {
		.arr = pool,
		.size = 1024,
		.ss = 0
	};

	int *curr = &info->updates.curr;

	Array *arr = &info->updates.arrays[*curr];

	str = strtok_r(str, ",", &save_ptr);
	if (str)
		arr->arr[arr->ss++] = atoi(str);
	while(*save_ptr)
	{
		str = strtok_r(NULL, ",", &save_ptr);
		if (str)
			arr->arr[arr->ss++] = atoi(str);
	}

	arr->size = arr->ss;
	arr->ss = 0;

	ft_print_int_tab(arr->arr, arr->size, "\n");

	Node **order = &info->order[*curr];

	arr->ss = 0;
	while (arr->ss < arr->size)
		place_static(&np, order, (Point){arr->arr[arr->ss], arr->ss++});
	arr->ss = 0;
	(*curr)++;
}

void apply(gpointer data, gpointer user_data)
{
	char *str = data;
	t_info *info = user_data;

	if (*str == '\0')
		info->state = updates;
	else
	{
		if (info->state == rules) append_rules(str, info);
		else append_updates(str, info);
	}
	free(str);
}

#define POINTS_COUNT 16384
#define ARRAY_COUNT 1024
#define ELEMENT_COUNT 1024

void init_info(t_info *info)
{
	static Point points[POINTS_COUNT];
	static Array updates[ARRAY_COUNT];

	static int static_data[ARRAY_COUNT][ELEMENT_COUNT];
	static Node	*order[ARRAY_COUNT] = { [0 ... ARRAY_COUNT - 1] = NULL };

	info->order = order;

	info->rules = (PointArray){.arr = points, .size = POINTS_COUNT, .ss = 0};

	int i = -1;
	while (++i < ARRAY_COUNT) {
		memset(static_data[i], 0, sizeof(int) * ELEMENT_COUNT);
		updates[i] = (Array) { .arr = static_data[i], .size = ELEMENT_COUNT, .ss = 0 };
	}
	info->updates = (TwoDArray){
		.arrays = updates,
		.size = ARRAY_COUNT,
		.curr = 0
	};

}

void prepare(t_info *info)
{
	init_info(info);
	GList *input = read_file();
	g_list_foreach(input, apply, info);
	g_list_free(input);
	input = NULL;

	info->rules.size = 	info->rules.ss;
	info->rules.ss = 0;
}

int is_valid_sequence(t_info *info, int idx, int *m)
{
	PointArray *rules = &info->rules;

	Array a = info->updates.arrays[idx];
	Node **hmap = &info->order[idx];

	rules->ss = 0;
	while(rules->ss < rules->size)
	{
		Point rule = rules->arr[rules->ss++];
		Node *left = get(hmap, rule.x);
		if (!left) continue;
		Node *right = get(hmap, rule.y);
		if (!right) continue;
		if (left->idx > right->idx)
			return (*m = 0, false);
	}
	int middle = a.arr[a.size / 2];
	return (*m = middle, true);
}

int part1(t_info *info)
{
	long acc = 0;
	info->updates.size = info->updates.curr;

	info->updates.curr = 0;
	while (info->updates.curr < info->updates.size)
	{
		int middle = 0;
		if (is_valid_sequence(info, info->updates.curr++, &middle))
			acc += middle;
	}

	return ((int)acc);
}

int reorder(t_info *info, int idx)
{

	return (0);
}

int part2(t_info *info)
{
	long acc = 0;
	info->updates.curr = 0;
	while (info->updates.curr < info->updates.size)
	{
		int middle = 0;
		int idx = info->updates.curr++;
		if (!is_valid_sequence(info, idx, &middle))
		{
			middle = reorder(info, idx);
			acc += middle;
		}

	}
	return ((int)acc);
}

int main(void)
{
	static t_info	info = { .state = rules };

	prepare(&info);

	printf("part1: %d\n=====================================\n", part1(&info));
	printf("part2: %d\n", part2(&info));

	return (EX_OK);
}

GList *read_file()
{
	char *lineptr = NULL;
	GList *input = NULL;
	size_t n;
	ssize_t nread;

	FILE *f = fopen(INPUT_FILE_NAME, "r");
	while ((nread = getline(&lineptr, &n, f)) > 0)
	{
		lineptr[nread - 1] = '\0';
		input = g_list_append(input, strdup(lineptr));
		*lineptr = '\0';
	}
	lineptr = (free(lineptr), NULL);
	fclose(f);
	return (input);
}