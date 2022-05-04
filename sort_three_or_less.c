/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three_or_less.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ean <ean@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 09:11:48 by ean               #+#    #+#             */
/*   Updated: 2022/02/28 09:48:11 by ean              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort_three_or_less.h"
#include "indexing.h"
#include "moves.h"

void	sort_three_or_less(t_ring *a)
{
	int	max_index;
	int	size;

	size = ring_size(a);
	if (size == 1)
		return ;
	max_index = find_max_index(a);
	if (max_index == size - 2)
		execute_move_n_times(a, NULL, RRA, 1);
	else if (max_index == 0)
		execute_move_n_times(a, NULL, RA, 1);
	if (nth_val(a, 0) > nth_val(a, 1))
		execute_move_n_times(a, NULL, SA, 1);
}
