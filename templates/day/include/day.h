#ifndef __PROJECT_NAME___H
#define __PROJECT_NAME___H

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

#endif //__PROJECT_NAME___H