/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day14.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 00:53:11 by abelov            #+#    #+#             */
/*   Updated: 2025/08/27 00:53:11 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DAY14_H
#define DAY14_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <glib.h>
#include <sys/queue.h>
//#include <linux/list.h>
#include <utlist.h>
#include <stdlib.h>
#include "aoc_2024_defs.h"

#ifndef INPUT_FILE_NAME
# define INPUT_FILE_NAME "./resources/input"
#endif

//#define AREA_WIDTH 101
//#define AREA_HEIGHT 103

#define AREA_WIDTH 11
#define AREA_HEIGHT 7

typedef struct Robot
{
	Point p;
	Point v;
	LIST_ENTRY(Robot) link; /* intrusive linkage */
}	Robot;

LIST_HEAD(RobotList, Robot);

typedef struct s_item
{
	char			*str;
	struct s_item	*next;
}	StringListItem;

typedef struct s_info
{
	char				area[AREA_WIDTH * AREA_HEIGHT];
	int					waitTime;
	struct RobotList	robots;
}	t_info;

int part1(t_info *game);
long part2(t_info *game);

void prepare(t_info *p_info);

#endif //DAY14_H
