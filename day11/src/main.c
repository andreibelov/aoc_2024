/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:58:50 by abelov            #+#    #+#             */
/*   Updated: 2024/12/30 18:58:52 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "day11.h"
#include "aoc_2024.h"
#include <sysexits.h>
#include <stdio.h>

uint64_t blinkRec(uint64_t rock, int blinks, Node **cache)
{
	if (blinks == 0) return 1;
	char buf[20];

	Node *cached = get(*cache, (Point) {.x = rock, .y = blinks});
	if (cached) return cached->val;

	uint64_t result = 0;

	if (rock == 0)
		result = blinkRec(1, blinks - 1, cache);
	else if (snprintf(buf, 20, "%lu", rock) % 2 == 0)
	{
		int nblen = strlen(buf);
		uint64_t right = atoll(buf + nblen / 2);
		buf[nblen / 2] = '\0';
		uint64_t left = atoll(buf);
		result = blinkRec(left, blinks - 1, cache)
				 + blinkRec(right, blinks - 1, cache);
	}
	else
		result = blinkRec(rock * 2024, blinks - 1, cache);
	place(cache, (Point){.x = rock, .y = blinks}, result);
	return (result);
}

uint64_t	blink(uint64_t rock, int blinks, Node **cache)
{
	StackFrame stack[STACK_MAX];
	int sp = 0;
	uint64_t result_so_far = 0; // Stores the result of the most recent computation
	char buf[20];

	stack[sp++] = (StackFrame) {.rock = rock, .blinks = blinks, .state = PROCESS_START};
	while(sp)
	{
		StackFrame *frame = &stack[sp - 1];

		if (frame->blinks == 0)
		{
			result_so_far = 1;
			sp--;
			continue;
		}

		if (frame->rock == 0)
		{
			frame->blinks--;
			frame->rock = 1;
			continue;
		}

		Node *cached = get(*cache, (Point) {.x = frame->rock, .y = frame->blinks});
		if (cached)
		{
			result_so_far = cached->val;
			sp--;
			continue;
		}

		int buflen = snprintf(buf, 20, "%lu", frame->rock);
		if (frame->state == PROCESS_START && buflen % 2 == 0) // Split into left and right
		{
			frame->state = PROCESS_LEFT; // Process left next
			frame->right = atoll(buf + buflen / 2);
			buf[buflen / 2] = '\0';
			frame->left = atoll(buf);
			stack[sp++] = (StackFrame) {.rock = frame->left, .blinks = frame->blinks - 1, .state = PROCESS_START};
		}
		else if (frame->state == PROCESS_LEFT) // Left result obtained, proceed with right
		{
			frame->left = result_so_far;
			frame->state = PROCESS_RIGHT;
			stack[sp++] = (StackFrame) {.rock = frame->right, .blinks = frame->blinks - 1, .state = PROCESS_START};
		}
		else if (frame->state == PROCESS_RIGHT) // Combine left and right results
		{
			sp--;
			result_so_far = frame->left + result_so_far;
			place(cache, (Point){.x = frame->rock, .y = frame->blinks}, result_so_far);
		}
		else // Multiply and recurse
		{
			frame->blinks--;
			frame->rock *= 2024;
		}
	}

	return (result_so_far);
}

uint64_t part1(t_info *info)
{
	uint64_t acc = 0;
	Node *lut = NULL, *iter, *tmp;

	Array *arr = &info->input;

	arr->ss = 0;
	while (arr->ss < arr->size)
	{
		acc += blink(arr->arr[arr->ss], 25, &lut);
		arr->ss++;
	}

	HASH_ITER(hh, lut, iter, tmp)
	{
		HASH_DEL(lut, iter);
		free(iter);
	}

	return (acc);
}

uint64_t part2(t_info *info)
{
	uint64_t acc = 0;

	Node *lut = NULL, *iter, *tmp;

	Array *arr = &info->input;

	arr->ss = 0;
	while (arr->ss < arr->size)
	{
		acc += blink(arr->arr[arr->ss], 75, &lut);
		arr->ss++;
	}

	HASH_ITER(hh, lut, iter, tmp)
	{
		HASH_DEL(lut, iter);
		free(iter);
	}

	return (acc);
}

void prepare(t_info *info)
{
	char	*save_ptr;
	char 	strbuf[1024];

	static int starr[ARRAY_COUNT][ELEMENT_COUNT];

	Array *arr = &(Array){ .arr = starr[0], .ss = 0, .size = ELEMENT_COUNT};

	GList *input = read_file();
	char *input_str = strdup(g_list_nth(input, 0)->data);
	g_list_free_full(input, free);
	input = NULL;

	errno = 0;
	long val = strtol(input_str, &save_ptr, 10);
	if (!(errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) && !(errno != 0 && val == 0))
		arr->arr[arr->ss++] = (int) val;

	while (save_ptr && *save_ptr)
	{
		errno = 0;
		val = strtol(save_ptr, &save_ptr, 10);
		if (!(errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) && !(errno != 0 && val == 0))
			arr->arr[arr->ss++] = (int) val;
		else
		{
			snprintf(strbuf, 1024, "error parsing the line: %s", input_str);
			free(input_str);
			perror(strbuf);
			exit(EX_DATAERR);
		}
	}
	arr->size = arr->ss;
	arr->ss = 0;

	info->input = *arr;

	free(input_str);
}

int main(void)
{
	static t_info	info;
	prepare(&info);

	printf("part1: %lu\n=====================================\n", part1(&info));
	printf("part2: %lu\n", part2(&info));
	return (EX_OK);
}
