/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 13:07:04 by abelov            #+#    #+#             */
/*   Updated: 2024/12/01 13:07:05 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sysexits.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include "day1.h"

#ifndef INPUT_FILE_NAME
# define INPUT_FILE_NAME "./resources/input.txt"
#endif

#include <uthash.h>
typedef struct
{
	long key;
	int value;
	UT_hash_handle hh;
}	hash_entry;

#define MAX_LIST_SIZE 1024

int parse_input(int *list1, int *list2);

int part2(void)
{
	int listsize;
	int list1[MAX_LIST_SIZE];
	int list2[MAX_LIST_SIZE];

	long acc = 0;
	int i;

	long key;
	hash_entry *table = NULL, *iter, *tmp;
	hash_entry *entry;

	listsize = parse_input((int *) &list1, (int *) &list2);

	i = -1;
	while(++i < listsize)
	{
		key = list2[i];
		HASH_FIND(hh, table, &key, sizeof(long), entry);
		if (!entry)
		{
			entry = (hash_entry *)malloc(sizeof(hash_entry));
			if (!entry) return (-1);
			entry->key = key;
			HASH_ADD(hh, table, key, sizeof(long), entry);
			entry->value = 0;
		}
		entry->value++;
	}

	i = -1;
	while(++i < listsize)
	{
		key = list1[i];
		HASH_FIND(hh, table, &key, sizeof(long), entry);
		if (!entry)
			continue;
		acc += key * entry->value;
	}

	HASH_ITER(hh, table, iter, tmp)
	{
		HASH_DEL(table, iter);
		free(iter);
	}
	return ((int )acc);
}


int part1(void )
{
	long acc = 0;
	int i = -1;

	int list1[MAX_LIST_SIZE];
	int list2[MAX_LIST_SIZE];

	int listsize = parse_input((int *) &list1, (int *) &list2);

	qsort(list1, listsize, sizeof(int), intcmp_f);
	qsort(list2, listsize, sizeof(int), intcmp_f);

	i =-1;
	while (++i < listsize)
		acc += MAX(list1[i], list2[i]) - MIN(list1[i], list2[i]);
	return ((int )acc);
}

int main(void)
{
	printf("part1: %d\n", part1());
	printf("part2: %d\n", part2());
	return (EX_OK);
}


int parse_input(int *list1, int *list2)
{
	int listsize = 0;
	long val1 = 0;
	long val2 = 0;

	char *lineptr = NULL;
	char *endptr = NULL;
	size_t n;
	ssize_t nread;

	FILE *f = fopen(INPUT_FILE_NAME, "r");

	while ((nread = getline(&lineptr, &n, f)) > 0)
	{
		errno = 0;
		val1  = (int)strtol(lineptr, &endptr, 10);
		if ((errno == ERANGE && (val1 == LONG_MAX || val1 == LONG_MIN))
			|| (errno != 0 && val1 == 0)) {
			perror("strtol");
			break;
		}
		else
		{
			errno = 0;
			val2  = (int)strtol(endptr, &endptr, 10);
			if ((errno == ERANGE && (val2 == LONG_MAX || val2 == LONG_MIN))
				|| (errno != 0 && val2 == 0)) {
				perror("strtol");
				break;
			}
			else
			{
				list1[(unsigned int)listsize] = val1;
				list2[(unsigned int)listsize] = val2;
				listsize++;
			}
		}
		*lineptr = '\0';
	}
	lineptr = (free(lineptr), NULL);
	fclose(f);
	return ((int)listsize);
}
