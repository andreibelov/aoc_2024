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

long get_match_p1(const char *lineptr);

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
	return (int)acc;
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
		val1  = (int)strtol(&search_start[matches[++i].rm_so], &endptr, 10);
		if (!(errno == ERANGE && (val1 == LONG_MAX || val1 == LONG_MIN)) && !(errno != 0 && val1 == 0))
		{
			errno = 0;
			endptr = NULL;
			val2  = (int)strtol(&search_start[matches[++i].rm_so], &endptr, 10);

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

int part2()
{
	const char *pattern = "mul\\(([0-9]{1,3}),([0-9]{1,3})\\)|do()|don't()"; // Example regex: matches "word number"
	const char *text = "xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))";    // Target text to match against

	regex_t regex;
	int ret;

	// Compile the regex
	ret = regcomp(&regex, pattern, REG_EXTENDED);
	if (ret != 0) {
		print_error(ret, &regex);
		return 1;
	}

	regmatch_t matches[MAX_MATCHES];
	const char *search_start = text;

	// Loop to find all matches in the text
	while (1) {
		ret = regexec(&regex, search_start, MAX_MATCHES, matches, 0);
		if (ret == REG_NOMATCH) {
			break;
		} else if (ret != 0) {
			print_error(ret, &regex);
			regfree(&regex);
			return 1;
		}

		// Print all captured groups
		printf("Match found:\n");
		for (size_t i = 0; i < MAX_MATCHES && matches[i].rm_so != -1; i++) {
			int start = matches[i].rm_so;
			int end = matches[i].rm_eo;
			printf("  Group %zu: %.*s\n", i, end - start, search_start + start);
		}

		// Move the start position to continue searching
		search_start += matches[0].rm_eo;
	}

	// Free the compiled regex
	regfree(&regex);
	return 0;
}

int main(void)
{
	printf("part1: %d\n\n=====================================\n\n", part1());
	printf("part2: %d\n", part2());
	return (EX_OK);
}
