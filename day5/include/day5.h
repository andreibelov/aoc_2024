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

typedef struct UT_hash_handle1 {
	struct UT_hash_table *tbl;
	void *prev;                       /* prev element in app order      */
	void *next;                       /* next element in app order      */
	struct UT_hash_handle *hh_prev;   /* previous hh in bucket order    */
	struct UT_hash_handle *hh_next;   /* next hh in bucket order        */
	int *key;                        /* ptr to enclosing struct's key  */
	unsigned keylen;                  /* enclosing struct's key len     */
	unsigned hashv;                   /* result of hash-fcn(key)        */
} UT_hash_handle1;

typedef struct he1
{
	int key;
	int idx;
	UT_hash_handle1 hh;
}	Node1;

typedef struct NodeArray
{
	Node *arr;
	int size;
	int ss;
}	NodeArray;

#endif //DAY5_H
