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
#include <stdbool.h>
#include <math.h>
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

	eq->test_val = atoll(str);

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

	info->size = info->ss;
	info->ss = 0;
}

typedef struct entry
{
	long long value_so_far;
	int index;
}	entry;

int	nbrlen(long long nbr)
{
	int acc = 0;
	const unsigned int	radix = 10;

	while (nbr > 0)
	{
		nbr = nbr / radix;
		acc++;
	}
	return (acc);
}

int isReachable(long long target, Array chain)
{
	entry stack[1024];
	int ss = 0;
	int next;
	int retval = false;

	stack[ss++] = (entry){chain.arr[0], 1 };
	while (ss)
	{
		entry e = stack[--ss];
		if (e.index == chain.size)
		{
			if (e.value_so_far == target)
			{
				retval = true;
				break;
			}
			else continue;
		}
		next = chain.arr[e.index];
		stack[ss++] = (entry){ e.value_so_far + next, e.index + 1};
		stack[ss++] = (entry){ e.value_so_far * next, e.index + 1};
	}

	return (retval);
}

int isReachableCat(long long target, Array chain)
{
	static int pow10[10] = {
		1, 10, 100, 1000, 10000,
		100000, 1000000, 10000000, 100000000, 1000000000
	};
	entry stack[1024];
	int ss = 0;
	int next;
	int retval = false;

	stack[ss++] = (entry){chain.arr[0], 1 };
	while (ss)
	{
		entry e = stack[--ss];
		if (e.index == chain.size)
		{
			if (e.value_so_far == target)
			{
				retval = true;
				break;
			}
			else continue;
		}
		next = chain.arr[e.index];
		stack[ss++] = (entry){ e.value_so_far + next, e.index + 1};
		stack[ss++] = (entry){ e.value_so_far * next, e.index + 1};
		long long cat = (e.value_so_far * pow10[(unsigned int)nbrlen(next)]) + next;
		stack[ss++] = (entry){ cat, e.index + 1};
	}

	return (retval);
}

int isReachableRec(long long test_number, Array chain, long long value_so_far)
{
	int left, right;

	if (chain.size == 0) return (test_number == value_so_far);

	left = isReachableRec(test_number, (Array){.arr = &chain.arr[1], .size = chain.size - 1 }, value_so_far * chain.arr[0]);
	right = isReachableRec(test_number, (Array){.arr = &chain.arr[1], .size = chain.size - 1 }, value_so_far + chain.arr[0]);

	return (left || right);
}

int isReachableCatRec(long long test_number, Array chain, long long value_so_far)
{
	if (chain.size == 0) return (test_number == value_so_far);

	long long next = chain.arr[0];
	int left, right, middle = false;
	Array a = (Array){.arr = &chain.arr[1], .size = chain.size - 1 };

	long long cat = (value_so_far * pow(10, nbrlen(next))) + next;
	middle = isReachableCatRec(test_number, a,cat);
	left = isReachableCatRec(test_number, a, value_so_far * next);
	right = isReachableCatRec(test_number, a, value_so_far + next);

	return (left || right || middle);
}

long long part1(t_info *info)
{
	long long acc = 0;

	info->ss = -1;
	while (++(info->ss) < info->size)
	{
		t_eq *eq = &info->equations[info->ss];
		if (isReachable(eq->test_val, eq->operands))
			acc += eq->test_val;
	}
	return (acc);
}

long long part2(t_info *info)
{
	long long acc = 0;

	info->ss = -1;
	while (++(info->ss) < info->size)
	{
		t_eq *eq = &info->equations[info->ss];
		if (isReachableCat(eq->test_val, eq->operands))
			acc += eq->test_val;
	}
	return (acc);
}

int main(void)
{
	static t_info	info;
	prepare(&info);

	printf("part1: %lld\n=====================================\n", part1(&info));
	printf("part2: %lld\n", part2(&info));
	return (EX_OK);
}
