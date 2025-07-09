/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:23:19 by abelov            #+#    #+#             */
/*   Updated: 2025/07/07 21:23:20 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sysexits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "day13.h"

int main(void)
{
	t_info	info = {.costs = (Cost){ .x = 3, .y = 1 }};
	prepare(&info);

	printf("part1: %d\n=====================================\n", part1(&info));
	printf("part2: %d\n", part2(&info));
	return (EX_OK);
}


/**
 * Given a Claw machine and pointers to ints for solution,
 * solve for nA, nB using Cramer's rule:
 *   nA * Ax + nB * Bx = Px
 *   nA * Ay + nB * By = Py
 * Returns 1 if there is a unique integer solution,
 * writes solution to *nA, *nB.
 * Returns 0 otherwise.
 */
int solve_claw_cramer(const Claw machine, int *nA, int *nB)
{
	int Ax = machine.A.x;
	int Ay = machine.A.y;
	int Bx = machine.B.x;
	int By = machine.B.y;
	int Px = machine.prize.x;
	int Py = machine.prize.y;

	int D  = Ax * By - Ay * Bx;      // Main determinant
	int Da = Px * By - Py * Bx;      // Determinant with Px, Py for A
	int Db = Ax * Py - Ay * Px;      // Determinant with Px, Py for B

	if (D == 0)
	{
		dprintf(STDERR_FILENO, "No unique solution: D=0\n");
		return 0;
	}
	if (Da % D != 0 || Db % D != 0) 	// Check integer divisibility
	{
		dprintf(STDERR_FILENO, "No integer solution for this machine\n");
		return 0;
	}

	int solA = Da / D;
	int solB = Db / D;

	if (solA < 0 || solB < 0) 	// Only allow non-negative solutions
	{
		dprintf(STDERR_FILENO, "Negative button presses not allowed\n");
		return 0;
	}

	*nA = solA;
	*nB = solB;
	return 1;
}

int	part1(t_info *game)
{
	int result = 0;

	int i = -1;
	while (++i < game->sp)
	{
		Vector	count = {0x00};
		if (solve_claw_cramer(game->machines[i], &count.x, &count.y))
			result += 3 * count.x + count.y;
	}
	return (result);
}

int	part2(t_info *game)
{
	return (0);
}

void prepare(t_info *game)
{
	char	*buf = NULL;
	size_t	size;
	ssize_t	len;
	FILE	*f;

	f = fopen(INPUT_FILE_NAME, "r");

	size = 0;
	len = getline(&buf, &size, f);
	while (len != -1)
	{
		Claw	machine;
		char	*endptr;
		char	*tok;

		tok = strtok_r(strchr(buf, ':'), ",", &endptr);
		machine.A.x = (int)strtol(strchr(tok, '+'), NULL, 10);
		machine.A.y = (int)strtol(strchr(endptr, '+'), NULL, 10);
		getline(&buf, &size, f);

		tok = strtok_r(strchr(buf, ':'), ",", &endptr);
		machine.B.x = (int)strtol(strchr(tok, '+'), NULL, 10);
		machine.B.y = (int)strtol(strchr(endptr, '+'), NULL, 10);
		getline(&buf, &size, f);

		tok = strtok_r(strchr(buf, ':'), ",", &endptr);
		machine.prize.x = (int)strtol(strchr(tok, '=') + 1, NULL, 10);
		machine.prize.y = (int)strtol(strchr(endptr, '=') + 1, NULL, 10);
		getline(&buf, &size, f);

		game->machines[game->sp++] = machine;
		len = getline(&buf, &size, f);
	}
	free(buf);
	fclose(f);
}
