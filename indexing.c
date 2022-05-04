/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ean <ean@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:27:33 by ean               #+#    #+#             */
/*   Updated: 2022/02/28 10:46:39 by ean              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "indexing.h"

int	nth_val(const t_ring *r, const int n)
{
	int	remainder;
	int	index;

	remainder = n % ring_size(r);
	index = (r->front + 1 + remainder) % r->capacity;
	return (r->arr[index]);
}

int	find_max_index_in_sorted_ring(const t_ring *r)
{
	int	max_index;

	max_index = 0;
	while (nth_val(r, max_index + 1) > nth_val(r, max_index))
		++max_index;
	return (max_index);
}

int	find_max_index(const t_ring *r)
{
	int	max_index;
	int	size;
	int	i;

	max_index = 0;
	size = ring_size(r);
	i = 1;
	while (i < size)
	{
		if (nth_val(r, i) > nth_val(r, max_index))
			max_index = i;
		++i;
	}
	return (max_index);
}
