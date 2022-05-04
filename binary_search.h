/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ean <ean@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 09:59:14 by ean               #+#    #+#             */
/*   Updated: 2022/02/28 10:49:44 by ean              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_SEARCH_H
# define BINARY_SEARCH_H
# include "circular_buffer.h"

int	binary_search(const int *a, const int key, int n);
int	bsearch_new_len(const t_ring *seq, const int *tail, int len, const int val);
int	bsearch_top_index(const t_ring *s, int min, int max, const int val);

#endif
