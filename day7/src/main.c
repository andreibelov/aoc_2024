/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:31:31 by abelov            #+#    #+#             */
/*   Updated: 2024/12/11 22:31:31 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sysexits.h>
#include "aoc_2024.h"
#include "day7.h"

void apply(gpointer data, gpointer user_data)
{
	char 	*str = data;
	char	*save_ptr;
	char 	strbuf[1024];
	t_info	*info = user_data;

	str = strtok_r(str, ":", &save_ptr);

	t_eq *eq = &info->equations[info->ss++];

	eq->test_val = atoi(str);
	printf("%d: ", eq->test_val);

	Array *arr = &eq->operands;
	while (save_ptr && *save_ptr)
	{
		errno = 0;
		long val = strtol(save_ptr, &save_ptr, 10);
		if (!(errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) && !(errno != 0 && val == 0))
			arr->arr[arr->ss++] = (int) val;
		else
		{
			snprintf(strbuf, 1024, "error parsing the line: %s", str);
			free(str);
			perror(strbuf);
			exit(EX_DATAERR);
		}
	}

	arr->size = arr->ss;
	arr->ss = 0;


	ft_println_int_array(*arr);
	free(str);
}

void prepare(t_info *info)
{
	info->ss = 0;
	info->size = 1024;

	static int static_data[ARRAY_COUNT][ELEMENT_COUNT];

	int i = -1;
	while (++i < ARRAY_COUNT) {
		memset(static_data[i], 0, sizeof(int) * ELEMENT_COUNT);
		info->equations[i].operands = (Array) { .arr = static_data[i], .size = ELEMENT_COUNT, .ss = 0 };
	}

	GList *input = read_file();
	g_list_foreach(input, apply, info);
	g_list_free(input);
	input = NULL;
}

int part1(t_info *info)
{
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

GList *read_file()
{
	char *lineptr = NULL;
	GList *input = NULL;
	size_t n;
	ssize_t nread;
	char buf[1024];

	FILE *f = fopen(INPUT_FILE_NAME, "r");
	if (!f)
	{
		snprintf(buf, 1024, "error opening file %s", INPUT_FILE_NAME);
		perror(buf);
		exit(EX_IOERR);
	}
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
