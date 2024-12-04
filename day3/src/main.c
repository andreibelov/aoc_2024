/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 22:04:39 by abelov            #+#    #+#             */
/*   Updated: 2024/12/03 22:14:11 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sysexits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>
#include <limits.h>
#include <glib.h>
#include "day3.h"

#define MAX_MATCHES 3 // Maximum number of matches to extract

void print_error(int errcode, regex_t *regex)
{
	char errbuf[256];
	regerror(errcode, regex, errbuf, sizeof(errbuf));
	fprintf(stderr, "Regex error: %s\n", errbuf);
}

int part1()
{

	long acc = 0;
	char *lineptr = NULL;

	size_t n;
	ssize_t nread;

	FILE *f = fopen(INPUT_FILE_NAME, "r");
	while ((nread = getline(&lineptr, &n, f)) > 0)
	{
		acc += get_match_p1(lineptr);
		*lineptr = '\0';
	}
	lineptr = (free(lineptr), NULL);
	fclose(f);
	return (int) acc;
}

long get_match_p1(const char *lineptr)
{
	int i;
	long val1 = 0;
	long val2 = 0;
	int end;
	int start;
	char *endptr = NULL;
	long acc = 0;

	const char *pattern = "mul\\(([0-9]{1,3}),([0-9]{1,3})\\)"; // Example regex: matches "word number"

	regex_t regex;
	int ret;

	// Compile the regex
	ret = regcomp(&regex, pattern, REG_EXTENDED);
	if (ret != 0)
	{
		print_error(ret, &regex);
		return 0;
	}

	printf("%s\n", lineptr);

	regmatch_t matches[MAX_MATCHES];
	const char *search_start = lineptr;

	// Loop to find all matches in the text
	while (1)
	{
		ret = regexec(&regex, search_start, MAX_MATCHES, matches, 0);
		if (ret == REG_NOMATCH)
			break;
		else if (ret != 0)
		{
			print_error(ret, &regex);
			regfree(&regex);
			return (0);
		}

		i = 0;
		start = matches[i].rm_so;
		end = matches[i].rm_eo;

		printf("Match found: \"%.*s\"\n", end - start, search_start + start);

		errno = 0;
		endptr = NULL;
		val1 = (int) strtol(&search_start[matches[++i].rm_so], &endptr, 10);
		if (!(errno == ERANGE && (val1 == LONG_MAX || val1 == LONG_MIN)) && !(errno != 0 && val1 == 0))
		{
			errno = 0;
			endptr = NULL;
			val2 = (int) strtol(&search_start[matches[++i].rm_so], &endptr, 10);

			if (!(errno == ERANGE && (val2 == LONG_MAX || val2 == LONG_MIN)) && !(errno != 0 && val2 == 0))
			{
				printf("%ld*%ld = %ld\n", val1, val2, val1 * val2);
				acc += val1 * val2;
			}
			else
				break;
		}

		// Move the start position to continue searching
		search_start += matches[0].rm_eo;
	}
	// Free the compiled regex
	regfree(&regex);
	return (acc);
}

void	print_tok(gpointer data, gpointer user_data)
{
	char buf[1024] = {0};

	long *acc = user_data;
	t_token	*tok = data;

	static int initial_state = 1;

	if (!data || !user_data )
		return;

	if (tok->type == MUL_TOK)
	{
		sprintf(buf, "mul(X,Y) = %d", tok->n);
		if (initial_state)
			*acc += tok->n;
	}
	else if (tok->type == DO_TOK)
	{
		sprintf(buf, "do()");
		if (!initial_state)
			initial_state = 1;
	}
	else if (tok->type == DONT_TOK)
	{
		sprintf(buf, "don't()");
		if (initial_state)
			initial_state = 0;
	}

	puts(buf);

}

int part2()
{
	int listsize;
	char *lineptr = NULL;

	long acc = 0;
	GList *input = NULL;
	size_t n;
	ssize_t nread;

	FILE *f = fopen(INPUT_FILE_NAME"2", "r");
	while ((nread = getline(&lineptr, &n, f)) > 0)
	{
		input = tokenize(lineptr);
		g_list_foreach(input, print_tok, &acc);
		g_list_free(input);
		input = NULL;
		*lineptr = '\0';
	}
	lineptr = (free(lineptr), NULL);
	fclose(f);
	return ((int)acc);
}

int main(void)
{
	printf("part1: %d\n\n=====================================\n\n", part1());
	printf("part2: %d\n", part2());
	return (EX_OK);
}

t_token new_mul_tok(const char *search_start, regmatch_t matches[MAX_MATCHES])
{
	int i = 0;
	long val1 = 0, val2 = 0;
	t_token result = { .n = 0, .type = MUL_TOK };
	char *endptr = NULL;

	errno = 0;
	val1 = (int) strtol(&search_start[matches[++i].rm_so], &endptr, 10);
	if (!(errno == ERANGE && (val1 == LONG_MAX || val1 == LONG_MIN)) && !(errno != 0 && val1 == 0))
	{
		errno = 0;
		endptr = NULL;
		val2 = (int) strtol(&search_start[matches[++i].rm_so], &endptr, 10);

		if (!(errno == ERANGE && (val2 == LONG_MAX || val2 == LONG_MIN)) && !(errno != 0 && val2 == 0))
			result.n = (int) (val1 * val2);

	}
	return result;
}

#define MAX_LIST_SIZE 100024

GList *tokenize(char *text)
{
	const char *pattern = "mul\\(([0-9]{1,3}),([0-9]{1,3})\\)|do()|don't()";
	static regex_t regex;

	static t_token tokens[MAX_LIST_SIZE];
	static int ss = 0;

	int ret;

	GList *list = NULL;
	t_token *tok;
	// Compile the regex
	ret = regcomp(&regex, pattern, REG_EXTENDED);
	if (ret != 0)
	{
		print_error(ret, &regex);
		return (NULL);
	}

	regmatch_t matches[MAX_MATCHES];
	const char *search_start = text;

	// Loop to find all matches in the text
	while (1)
	{
		ret = regexec(&regex, search_start, MAX_MATCHES, matches, 0);
		if (ret == REG_NOMATCH)
			break;
		else if (ret != 0)
			return (print_error(ret, &regex), NULL);

		// Print all captured groups
		printf("Match found: %.*s\n", matches[0].rm_eo - matches[0].rm_so, search_start + matches[0].rm_so);

		if (!strncmp("mul(", search_start + matches[0].rm_so, 3))
			tokens[ss] = new_mul_tok(search_start, matches);
		else if (!strncmp("do(", search_start + matches[0].rm_so, 3))
			tokens[ss] = (t_token) {.n = 0, .type = DO_TOK};
		else if (!strncmp("don't(", search_start + matches[0].rm_so, 6))
			tokens[ss] = (t_token) {.n = 0, .type = DONT_TOK};

		tok = &tokens[ss++];

		list = g_list_append(list, tok);
		// Move the start position to continue searching
		search_start += matches[0].rm_eo;
	}

	// Free the compiled regex if needed
	regfree(&regex);

	return (list);
}
