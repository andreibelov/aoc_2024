/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 22:08:47 by abelov            #+#    #+#             */
/*   Updated: 2024/12/03 22:08:47 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DAY3_H
#define DAY3_H

#ifndef INPUT_FILE_NAME
# define INPUT_FILE_NAME "./resources/input.txt"
#endif

typedef enum token_type
{
	MUL_TOK = 0,
	DO_TOK,
	DONT_TOK,
}	t_token_type;

typedef struct s_token
{
	t_token_type 	type;
	int				n;
} t_token;

long get_match_p1(const char *lineptr);

GList *tokenize(char *string);

#endif //DAY3_H
