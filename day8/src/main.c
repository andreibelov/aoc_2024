/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 18:53:39 by abelov            #+#    #+#             */
/*   Updated: 2024/12/27 09:14:13 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sysexits.h>
#include "aoc_2024.h"
#include "day8.h"
#include <uthash.h>
#include <ctype.h>

#define ARRAY_COUNT 62
#define ELEMENT_COUNT 1024

static inline
unsigned char idx_to_char(const unsigned char idx)
{
	char c = 0;

	if (idx < 10)
		c = (char)('0' + idx);
	else if (idx < 36)
		c = (char)('A' + idx - 10);
	else if (idx < 62)
		c = (char)('a' + idx - 36);
	return (c);
}

static inline
int char_to_idx(unsigned char c)
{
	int idx = -1;

	if (isdigit(c))
		idx = c - '0';
	else if (isupper(c))
		idx = c - 'A' + 10;
	else if (islower(c))
		idx = c - 'a' + 36;

	return (idx);
}

void apply(gpointer data, gpointer user_data)
{
	char c;
	char *str = data;
	char *const ptr = data;
	t_info *info = user_data;

	while (*str)
	{
		c = *str;
		if (isalnum(c))
		{
			unsigned int idx = char_to_idx(c);
			PointArray *pa = info->freq[idx];
			pa->arr[pa->ss++] = (Point){.x = (int)(str - ptr), .y = info->max.y};
		}
		str++;
	}

	info->max.x = MAX(info->max.x, (int)(str - ptr));
	info->max.y++;
	free(ptr);
}

void prepare(t_info *info)
{
	info->max = (Point){.x = 0, .y = 0};
	info->ss = 0;
	info->size = ARRAY_COUNT;

	static PointArray *pap[ARRAY_COUNT] = {};
	static PointArray paz[ARRAY_COUNT];
	static Point static_data[ARRAY_COUNT][ELEMENT_COUNT] = {};

	int i = -1;
	while (++i < ARRAY_COUNT)
	{
		paz[i].arr = static_data[i];
		paz[i].ss = 0;
		paz[i].size = ELEMENT_COUNT;
		pap[i] = &paz[i];
	}

	info->freq = pap;

	GList *input = read_file();
	g_list_foreach(input, apply, info);
	g_list_free(input);

	i = -1;
	while (++i < ARRAY_COUNT)
	{
		PointArray *p = &paz[i];

		if (p->ss != 0)
		{
			p->size = p->ss;
			printf("%c ", idx_to_char(i));
			p->ss = 0;
			Point ant = p->arr[p->ss];
			printf("[(%d,%d)", ant.x, ant.y);
			while (++p->ss < p->size)
			{
				ant = p->arr[p->ss];
				printf(", (%d,%d)", ant.x, ant.y);
			}
			printf("]\n");

		}
		else pap[i] = NULL;
	}

	input = NULL;
}

int place_ans(t_info *info, int *acc)
{
	Node *anodes = NULL, *anodesP2 = NULL;

	Node *iter, *tmp;
	info->ss = -1;
	while(++info->ss < info->size)
	{
		PointArray *pa = info->freq[info->ss];
		if (pa)
		{
			pa->ss = -1;
			while (++pa->ss < pa->size)
			{
				Point p = pa->arr[pa->ss], q;

				if (pa->size > 1)
					place(&anodesP2, p);

				int j = pa->ss;
				while(++j < pa->size)
				{
					q = pa->arr[j];

					int k = 0;
					while (++k < info->max.x)
					{
						Point a, b, distance = mul(sub(p, q), k);
						a = sub(q, distance);
						b = add(p, distance);

						if (check_boundaries(a, info->max))
						{
							if (k == 1)
								place(&anodes, a);
							place(&anodesP2, a);
						}
						if (check_boundaries(b, info->max))
						{
							if (k == 1)
								place(&anodes, b);
							place(&anodesP2, b);
						}
					}
				}
			}

			pa->ss = 0;
		}

	}

	HASH_ITER(hh, anodes, iter, tmp)
	{
		(*acc)++;
		HASH_DEL(anodes, iter);
		free(iter);
	}

	int retval = 0;

	HASH_ITER(hh, anodesP2, iter, tmp)
	{
		retval++;
		HASH_DEL(anodesP2, iter);
		free(iter);
	}
	return retval;
}

int part1(t_info *info)
{
	int acc = 0;
	place_ans(info, &acc);

	info->ss = 0;
	return (acc);
}

int part2(t_info *info)
{
	int acc = 0;
	int acc2 = 0;
	acc2 = place_ans(info, &acc);

	info->ss = 0;
	return (acc2);
}

int main(void)
{
	static t_info	info;
	prepare(&info);

	printf("part1: %d\n=====================================\n", part1(&info));
	printf("part2: %d\n", part2(&info));
	return (EX_OK);
}
