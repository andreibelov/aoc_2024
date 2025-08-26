/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day13.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:19:22 by abelov            #+#    #+#             */
/*   Updated: 2025/07/07 21:19:23 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DAY13_H
#define DAY13_H

#include "aoc_2024_defs.h"

#ifndef INPUT_FILE_NAME
# define INPUT_FILE_NAME "./resources/input"
#endif

typedef struct Point Button;
typedef struct Point Prize;
typedef struct Point Cost;
typedef struct Point Vector;

typedef struct s_machine
{
	Button	A;
	Button	B;
	Prize	prize;
	int 	best_total;
}	Claw;

typedef struct s_info
{
	Claw	machines[400];
	int 	sp;
	Cost	costs;
}	t_info;

int part1(t_info *game);
long part2(t_info *game);

void prepare(t_info *p_info);

#endif //DAY13_H
