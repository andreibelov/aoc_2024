/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day5.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 23:37:48 by abelov            #+#    #+#             */
/*   Updated: 2024/12/05 23:37:48 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DAY5_H
#define DAY5_H

#include <uthash.h>
typedef struct he
{
	int key;
	int idx;
	UT_hash_handle hh;
}	Node;

typedef struct NodeArray
{
	Node *arr;
	int size;
	int ss;
}	NodeArray;

#endif //DAY5_H
