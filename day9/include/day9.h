/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day9.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:40:14 by abelov            #+#    #+#             */
/*   Updated: 2024/12/28 15:40:14 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DAY9_H
#define DAY9_H

#include "aoc_2024.h"

typedef struct block
{
	int is_file;
	int file_id;
	int gap_id;
} Block;

typedef struct block_array
{
	Block	*disk;
	int		size;
	int		ss;
}	BlockArray;

typedef struct minifile
{
	int		file_id;
	int		size;
	Block	*blocks[64];
} Minifile;

typedef struct minifs
{
	Minifile	*files;
	int			size;
	int			ss;
} Filesystem;

typedef struct s_info
{
	BlockArray	p1;
	BlockArray	p2;
	Filesystem	fs;
}	t_info;

#endif //DAY9_H
