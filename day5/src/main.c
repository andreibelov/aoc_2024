/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 23:37:14 by abelov            #+#    #+#             */
/*   Updated: 2024/12/06 13:00:10 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sysexits.h>
#include <glib.h>
#include <stdio.h>
#include "aoc_2024.h"

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
} t_info;

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

void apply(gpointer data, gpointer user_data)
{
	char *str = data;
	t_info *info = user_data;

	if (*str == '\0')
		info->state = updates;
	else
	{
		switch (info->state)
		{
			case rules:
				append_rules(str, info);
				break;
			case updates:
			{
				break;
			}
		}
	}
	free(str);
}

int main(void)
{
	GList *input = read_file();
	t_info info = { .state = rules, .rules = (PointArray){.arr = (Point[16384]){}, .size = 16384, .ss = 0}};

	g_list_foreach(input, apply, &info);
	g_list_free(input);
	input = NULL;

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