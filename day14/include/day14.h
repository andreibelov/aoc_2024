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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "aoc_2024_defs.h"

#ifndef INPUT_FILE_NAME
# define INPUT_FILE_NAME "./resources/input"
#endif

typedef struct s_info
{
}	t_info;

int part1(t_info *game);
long part2(t_info *game);

void prepare(t_info *p_info);

#endif //DAY14_H
