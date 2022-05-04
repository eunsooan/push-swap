/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ean <ean@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:27:27 by ean               #+#    #+#             */
/*   Updated: 2022/02/28 10:49:26 by ean              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_search.h"
#include "indexing.h"

int	binary_search(const int *a, const int key, int n)
{
	int	low;
	int	high;
	int	mid;

	low = 0;
	high = n - 1;
	while (low <= high)
	{
		mid = low + (high - low) / 2;
		if (a[mid] == key)
			return (mid);
		else if (a[mid] < key)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return (-1);
}

int	bsearch_new_len(const t_ring *seq, const int *tail, int len, const int val)
{
	int	low;
	int	high;
	int	mid;

	low = 1;
	high = len + 1;
	while (low < high)
	{
		mid = low + (high - low) / 2;
		if (nth_val(seq, tail[mid]) < val)
			low = mid + 1;
		else
			high = mid;
	}
	return (low);
}

int	bsearch_top_index(const t_ring *s, int min, int max, const int val)
{
	int	low;
	int	high;
	int	mid;
	int	size;

	size = ring_size(s);
	max += size;
	low = min;
	high = max + 1;
	while (low < high)
	{
		mid = low + (high - low) / 2;
		if (nth_val(s, mid) < val)
			low = mid + 1;
		else
			high = mid;
	}
	return (low % size);
}
