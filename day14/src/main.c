/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 00:53:11 by abelov            #+#    #+#             */
/*   Updated: 2025/08/27 00:53:11 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sysexits.h>
#include "day14.h"

int main(void)
{
	t_info	info = { .waitTime = 100 };
	t_info	*const game = &info;
	prepare(game);

	printf("part1: %d\n=====================================\n", part1(game));
	printf("part2: %ld\n", part2(game));

	Robot *rob = LIST_FIRST(&game->robots), *temp;
	while (rob != NULL) {
		temp = LIST_NEXT(rob, link);
		LIST_REMOVE(rob, link);  /* unlink from list */
		free(rob);               /* free memory */
		rob = temp;
	}
	return (EX_OK);
}

enum e_quadrant
{
	TL = 0,
	TR,
	BL,
	BR
};

int	part1(t_info *game)
{
	int			i;
	const int	waitTime = game->waitTime;
	char *const	area = game->area;
	int			result = 0;
	Robot		*r, robot;

	i = -1;
	while (++i < waitTime) {
		LIST_FOREACH(r, &game->robots, link) {
			robot = *r;

			robot.p.x = (robot.p.x + robot.v.x + AREA_WIDTH) % AREA_WIDTH;
			robot.p.y = (robot.p.y + robot.v.y + AREA_HEIGHT) % AREA_HEIGHT;

			*r = robot;
		}
	}

	memset(area, 0, AREA_WIDTH * AREA_HEIGHT);

	LIST_FOREACH(r, &game->robots, link) {
		robot = *r;
		area[robot.p.y * AREA_WIDTH + robot.p.x]++;
	}

	Point it = { .y = -1};
	while (++it.y < AREA_HEIGHT) {
		it.x = -1;
		while (++it.x < AREA_WIDTH) {
			char c = area[it.y * AREA_WIDTH + it.x];
			fprintf(stdout, "%c", c == 0 ? '.' : c + '0');
		}
		fprintf(stdout, "\n");
	}
	int quadrants[4] = {0x00};
	fprintf(stdout, "\n");
	it.y = -1;
	while (++it.y < AREA_HEIGHT) {
		it.x = -1;
		while (++it.x < AREA_WIDTH) {
			char c = area[it.y * AREA_WIDTH + it.x];
			if (it.x == (AREA_WIDTH / 2) || it.y == (AREA_HEIGHT / 2))
				c = ' ';
			else if (c != 0)
			{
				if (it.x < (AREA_WIDTH / 2) && it.y < (AREA_HEIGHT / 2))
					quadrants[TL] += c;
				else if (it.x > (AREA_WIDTH / 2) && it.y < (AREA_HEIGHT / 2))
					quadrants[TR] += c;
				else if (it.x < (AREA_WIDTH / 2) && it.y > (AREA_HEIGHT / 2))
					quadrants[BL] += c;
				else
					quadrants[BR] += c;
				c = (char) (c + '0');
			}
			else
				c = (char) '.';
			fprintf(stdout, "%c", c);
		}
		fprintf(stdout, "\n");
	}
	fprintf(stdout, "\n");
	fflush(stdout);

	result =  quadrants[TL] * quadrants[TR] * quadrants[BL] * quadrants[BR];
	return (result);
}

long	part2(t_info *game)
{
	long result = 0;

	(void)game;
	; // implement part2 here
	return (result);
}

void prepare(t_info *game)
{
	char			*buf = NULL;
	size_t			size;
	ssize_t			len;
	FILE			*f;
	StringListItem	*list = NULL, *it, *tmp;

	game->robots = (struct RobotList)LIST_HEAD_INITIALIZER(robots);
	f = fopen(INPUT_FILE_NAME, "r");

	size = 0;
	len = getline(&buf, &size, f);
	while (len != -1)
	{
		it = malloc(sizeof(StringListItem));
		it->str = strndup(buf, strchrnul(buf, '\n') - buf);
		LL_APPEND(list, it);
		len = getline(&buf, &size, f);
	}
	free(buf);
	fclose(f);

	LL_FOREACH(list, it)
	{
		char *ptr;
		char *tok = strtok_r(it->str, " ", &ptr);

		Robot robot;

		robot.p.x = atoi(strtok(strchrnul(tok, '=') + 1, ","));
		robot.p.y = atoi(strtok(NULL, ","));

		robot.v.x = atoi(strtok(strchrnul(ptr, '=') + 1, ","));
		robot.v.y = atoi(strtok(NULL, ","));

		Robot *r = malloc(sizeof(Robot));
		*r = robot;

		LIST_INSERT_HEAD(&game->robots, r, link);

	}

	Robot *rob;
	LIST_FOREACH(rob, &game->robots, link) {
		printf("Robot p=(%d,%d) v=(%d,%d)\n",
			   rob->p.x, rob->p.y, rob->v.x, rob->v.y);
	}

	LL_FOREACH_SAFE(list, it, tmp)
	{
		free(it->str);
		free(it);
	}

}
