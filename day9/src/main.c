/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:39:01 by abelov            #+#    #+#             */
/*   Updated: 2024/12/28 15:39:02 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sysexits.h>
#include "day9.h"
#include <uthash.h>
#include <stdbool.h>

void print_disk(const BlockArray *info)
{
	char buf[98304];
	char *curr = buf;
	int iter = 0;
	while(iter < info->size)
	{
		Block *b = &info->disk[iter++];
		if (b->is_file)
			snprintf(curr++, 98304, "%d", b->file_id);
		else *curr++ = '.';
	}
	*curr = '\0';

	printf("\"%s\"\n", buf);
}

void swap(Block *a, Block *b)
{
	if (!a || !b) return;
	Block tmp = *b;
	*b = *a;
	*a = tmp;
}

int get_next_avail_block(BlockArray *ba)
{
	int i = ba->ss;
	if (ba->disk[i].is_file)
	{
		while(++i < ba->size && ba->disk[i].is_file)
			;
		ba->ss = i;
	}
	return (ba->ss);
}

Block *get_next_avail_gap_of_size(BlockArray *ba, int size)
{
	int i = 0;
	Block *found = NULL;

	while(i < ba->size && !found)
	{
		if (ba->disk[i].is_file)
		{
			while(++i < ba->size && ba->disk[i].is_file)
				;
			if (i >= ba->size) break;
		}

		Block *current = &ba->disk[i];
		int j = 1;
		while(++i < ba->size && !ba->disk[i].is_file)
			j++;
		if (j >= size)
			found = current;
	}
	return found;
}


unsigned long long part1(t_info *info)
{
	unsigned long long acc = 0;

	BlockArray *ba = &info->p1;
	/* print_disk(ba); */

	ba->ss = 0;

	int ss = ba->size - 1;
	while(ss > ba->ss)
	{
		Block *b = &ba->disk[ss--];
		if (b->is_file)
		{
			int next = get_next_avail_block(ba);
			if (ss > ba->ss)
			{
				Block *a = &ba->disk[next];
				swap(a, b);
				/* print_disk(ba); */
			}
		}
	}
	/* print_disk(ba); */
	ba->ss = 0;
	while(ba->ss < ba->size)
	{
		Block *b = &ba->disk[ba->ss];
		if (b->is_file) acc += ba->ss++ * b->file_id;
		else ba->ss++;
	}

	return (acc);
}

unsigned long long part2(t_info *info)
{
	unsigned long long acc = 0;
	BlockArray *ba = &info->p2;
	Filesystem *fs = &info->fs;

	/* print_disk(ba); */

	ba->ss = 0;
	fs->ss = fs->size;

	while(fs->ss--)
	{
		Minifile *file = &fs->files[fs->ss];
		Block *a = file->blocks[0];
		Block *gap = get_next_avail_gap_of_size(ba, file->size);
		if (gap && gap < a)
		{
			int j = -1;
			while (++j < file->size) swap(a + j, gap + j);
			/* print_disk(ba); */
		}
	}

	ba->ss = 0;
	while(ba->ss < ba->size)
	{
		Block *b = &ba->disk[ba->ss];
		if (b->is_file) acc += ba->ss++ * b->file_id;
		else ba->ss++;
	}

	return (acc);
}

void prepare(t_info *info)
{
	static Block disk1[98304] = {};
	static Block disk2[98304] = {};
	static Minifile files[16384] = {};

	GList *input = read_file();
	char *input_str = strdup(g_list_nth(input, 0)->data);
	g_list_free_full(input, free);
	input = NULL;

	BlockArray *p1 = &info->p1;
	p1->disk = disk1;
	p1->ss = 0;

	int fileid = 0, gapid = 0, curr_id;
	int state = 1;
	char *ptr = input_str;
	while(*ptr)
	{
		int nbr = (*ptr++) - '0';
		if (state == 1)
		{
			curr_id = fileid++;
			while (nbr--)
			{
				Block *b = &p1->disk[p1->ss++];
				b->gap_id = -1;
				b->file_id = curr_id;
				b->is_file = true;
			}
			state = !state;
		}
		else
		{
			curr_id = gapid++;
			while (nbr--)
			{
				Block *b = &p1->disk[p1->ss++];
				b->gap_id = curr_id;
				b->file_id = -1;
				b->is_file = false;
			}
			state = !state;
		}
	}
	free(input_str);
	p1->size = p1->ss;
	p1->ss = 0;

	memcpy(disk2, disk1, sizeof(Block) * p1->size);

	BlockArray *p2 = &info->p2;
	p2->disk = disk2;
	p2->size = p1->size;
	p2->ss = 0;

	Filesystem *fs = &info->fs;
	fs->files = files;
	fs->ss = 0;

	p2->ss = 0;
	while(p2->ss < p2->size)
	{
		Block *b = &p2->disk[p2->ss++];
		if (b->is_file)
		{
			int filesize = 1;
			while (p2->ss < p2->size && p2->disk[p2->ss].file_id == b->file_id)
			{
				filesize++;
				p2->ss++;
			}
			fs->files[fs->ss++] = (Minifile){.file_id = b->file_id,
											 .size = filesize, .blocks[0] = b};
		}
	}

	fs->size = fs->ss;
	fs->ss = 0;
}

int main(void)
{
	static t_info	info;
	prepare(&info);

	printf("part1: %llu\n=====================================\n", part1(&info));
	printf("part2: %llu\n", part2(&info));
	return (EX_OK);
}
