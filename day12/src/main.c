/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 17:44:25 by abelov            #+#    #+#             */
/*   Updated: 2024/12/31 17:44:27 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sysexits.h>
#include "day12.h"
#include "aoc_2024.h"

void apply(gpointer data, gpointer user_data)
{
	StringArray *strings = user_data;
	strings->arr[strings->current++] = data;
	printf("%s\n", (char *)data);
}

void prepare(t_info *info)
{
	GList *input = read_file();

	info->strings.current = 0;
	info->strings.size = (int)g_list_length(input);
	info->strings.arr = (char **)malloc(info->strings.size * sizeof(char *));

	g_list_foreach(input, apply, &info->strings);
	g_list_free(input);
	input = NULL;
}

int part1(t_info *info)
{
	Node *visited, *iter = NULL, *tmp = NULL;

	place(&visited, (Point){}, Right);

	HASH_ITER(hh, visited, iter, tmp)
	{
		HASH_DEL(visited, iter);
		free(iter);
	}
	return (0);
}

int part2(t_info *info)
{
	return (0);
}

int main(void)
{
	static t_info	info;
	prepare(&info);

	printf("part1: %d\n=====================================\n", part1(&info));
	printf("part2: %d\n", part2(&info));
	return (EX_OK);
}
