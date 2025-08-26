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
	t_info	info = {};
	prepare(&info);

	printf("part1: %d\n=====================================\n", part1(&info));
	printf("part2: %ld\n", part2(&info));
	return (EX_OK);
}

int	part1(t_info *game)
{
	int result = 0;

	(void)game;
	; // implement part1 here
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
	char	*buf = NULL;
	size_t	size;
	ssize_t	len;
	FILE	*f;

	f = fopen(INPUT_FILE_NAME, "r");

	size = 0;
	len = getline(&buf, &size, f);
	while (len != -1)
	{
		(void)game;
		; // write initialization code here
		len = getline(&buf, &size, f);
	}
	free(buf);
	fclose(f);
}
