/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:10:44 by abelov            #+#    #+#             */
/*   Updated: 2024/12/01 17:10:45 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DAY1_H
#define DAY1_H

#define intcmp_f (__compar_fn_t) intcmp

int intcmp(const int *a, const int *b)
{ return (*a > *b) - (*a < *b); }

int MIN(int X, int Y)
{ return ((X) < (Y)) ? (X) : (Y); }

int MAX(int X, int Y)
{ return ((X) > (Y)) ? (X) : (Y); }

#endif //DAY1_H
