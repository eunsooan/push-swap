/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertion_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ean <ean@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 09:09:15 by ean               #+#    #+#             */
/*   Updated: 2022/02/28 09:10:09 by ean              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "insertion_sort.h"
#include "indexing.h"
#include "moves.h"
#include "binary_search.h"
#define INT_MAX 2147483647

static void		calc_all_cost(t_cost *tab, t_ring *dst, t_ring *src, int max);
static t_cost	calc_cost(int dst_count, int src_count);
static int		get_index_with_min_cost(t_cost *tab, int val_count);
static void		insert_in_order(t_ring *dst, t_ring *src, t_cost cnt, int *max);

void	insertion_sort(t_ring *dst, t_ring *src)
{
	t_cost	*cost_table;
	int		min_index;
	int		max_index;
	int		val_count;
	int		val_to_insert_i;

	val_count = ring_size(src);
	cost_table = malloc(sizeof(*cost_table) * val_count);
	if (cost_table == NULL)
		exit(EXIT_FAILURE);
	max_index = find_max_index_in_sorted_ring(dst);
	while (val_count > 0)
	{
		calc_all_cost(cost_table, dst, src, max_index);
		val_to_insert_i = get_index_with_min_cost(cost_table, val_count);
		insert_in_order(dst, src, cost_table[val_to_insert_i], &max_index);
		--val_count;
	}
	min_index = (max_index + 1) % ring_size(dst);
	if (min_index <= ring_size(dst) / 2)
		execute_move_n_times(dst, NULL, RA, min_index);
	else
		execute_move_n_times(dst, NULL, RRA, ring_size(dst) - min_index);
	free(cost_table);
}

static void	calc_all_cost(t_cost *tab, t_ring *dst, t_ring *src, int max)
{
	int	i;
	int	dst_size;
	int	src_size;
	int	src_move_count;
	int	dst_move_count;

	i = 0;
	dst_size = ring_size(dst);
	src_size = ring_size(src);
	while (i < src_size)
	{
		src_move_count = i;
		if (src_move_count > src_size / 2)
			src_move_count = src_move_count - src_size;
		dst_move_count = bsearch_top_index(dst, max + 1, max, nth_val(src, i));
		if (dst_move_count > dst_size / 2)
			dst_move_count = dst_move_count - dst_size;
		tab[i] = calc_cost(dst_move_count, src_move_count);
		++i;
	}
}

static t_cost	calc_cost(int dst_count, int src_count)
{
	t_cost	new_cost;

	if (dst_count * src_count <= 0)
	{
		new_cost.dst_r_count = dst_count;
		new_cost.src_r_count = src_count;
		new_cost.rr_count = 0;
	}
	else if ((dst_count > 0 && dst_count > src_count)
		|| (dst_count < 0 && dst_count < src_count))
	{
		new_cost.dst_r_count = dst_count - src_count;
		new_cost.src_r_count = 0;
		new_cost.rr_count = src_count;
	}
	else
	{
		new_cost.dst_r_count = 0;
		new_cost.src_r_count = src_count - dst_count;
		new_cost.rr_count = dst_count;
	}
	return (new_cost);
}

static int	get_index_with_min_cost(t_cost *tab, int val_count)
{
	int	cost;
	int	min_cost;
	int	i;
	int	min_index;

	min_cost = INT_MAX;
	i = 0;
	while (i < val_count)
	{
		if (tab[i].rr_count == 0)
			cost = tab[i].src_r_count - tab[i].dst_r_count;
		else
			cost = tab[i].rr_count + tab[i].src_r_count + tab[i].dst_r_count;
		cost *= (cost > 0) * 1 + (cost < 0) * (-1);
		if (cost < min_cost)
		{
			min_cost = cost;
			min_index = i;
		}
		++i;
	}
	return (min_index);
}

static void	insert_in_order(t_ring *dst, t_ring *src, t_cost count, int *max)
{
	enum e_move	move;

	if (count.dst_r_count >= 0)
		move = RA;
	else
		move = RRA;
	execute_move_n_times(dst, NULL, move, count.dst_r_count);
	if (count.src_r_count >= 0)
		move = RB;
	else
		move = RRB;
	execute_move_n_times(NULL, src, move, count.src_r_count);
	if (count.rr_count >= 0)
		move = RR;
	else
		move = RRR;
	execute_move_n_times(dst, src, move, count.rr_count);
	*max += ring_size(dst) - count.dst_r_count - count.rr_count;
	*max %= ring_size(dst);
	if (nth_val(src, 0) > nth_val(dst, *max))
		*max = 0;
	else
		*max += 1;
	execute_move_n_times(dst, src, PA, 1);
}
