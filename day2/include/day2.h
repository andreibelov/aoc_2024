/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:46:49 by abelov            #+#    #+#             */
/*   Updated: 2024/12/02 10:46:51 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DAY2_H
#define DAY2_H

#include <uthash.h>

#ifndef INPUT_FILE_NAME
# define INPUT_FILE_NAME "./resources/input.txt"
#endif

typedef struct
{
	long key;
	int value;
	UT_hash_handle hh;
}	hash_entry;

#define MAX_LIST_SIZE 1024


#endif //DAY2_H
