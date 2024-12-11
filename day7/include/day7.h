/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day7.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:32:07 by abelov            #+#    #+#             */
/*   Updated: 2024/12/11 22:32:07 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DAY7_H
#define DAY7_H

#define ARRAY_COUNT 1024
#define ELEMENT_COUNT 1024

typedef struct s_eq
{
	int	test_val;
	Array operands;
}	t_eq;

typedef struct s_info
{
	t_eq	equations[ARRAY_COUNT];
	int		size;
	int		ss;
}	t_info;

GList *read_file();

#endif //DAY7_H
