/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lics.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ean <ean@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 14:50:53 by ean               #+#    #+#             */
/*   Updated: 2022/02/25 11:42:53 by ean              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lics.h"
#include "moves.h"
#include "binary_search.h"
#include "indexing.h"

static void	get_lics(int **lics, int *lics_len, t_ring *seq);
static int	get_lis_len(t_ring *seq, int i, int *back, int *tail);
static int	*make_lis(t_ring *seq, int len, int *back, int k);

void	filter_out_misplaced_elements(t_ring *stack, t_ring *bin)
{
	int	*lics;
	int	lics_len;
	int	misplaced_elements_count;

	lics = NULL;
	lics_len = 0;
	get_lics(&lics, &lics_len, stack);
	misplaced_elements_count = ring_size(stack) - lics_len;
	while (misplaced_elements_count)
	{
		if (binary_search(lics, nth_val(stack, 0), lics_len) < 0)
		{
			execute_move_n_times(stack, bin, PB, 1);
			--misplaced_elements_count;
		}
		else
			execute_move_n_times(stack, NULL, RA, 1);
	}
	free(lics);
}

static void	get_lics(int **lics, int *lics_len, t_ring *seq)
{
	int	*back_ptrs;
	int	*tail_ptrs;
	int	lis_len;
	int	i;
	int	seq_len;

	seq_len = ring_size(seq);
	back_ptrs = malloc(sizeof(*back_ptrs) * seq_len);
	tail_ptrs = malloc(sizeof(*tail_ptrs) * (seq_len + 1));
	if (back_ptrs == NULL || tail_ptrs == NULL)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < seq_len && *lics_len < seq_len)
	{
		lis_len = get_lis_len(seq, i, back_ptrs, tail_ptrs);
		if (lis_len > *lics_len)
		{
			*lics_len = lis_len;
			free(*lics);
			*lics = make_lis(seq, lis_len, back_ptrs, tail_ptrs[lis_len]);
		}
		++i;
	}
	free(back_ptrs);
	free(tail_ptrs);
}

static int	get_lis_len(t_ring *seq, int i, int *back, int *tail)
{
	int	seq_len;
	int	lis_len;
	int	new_len;
	int	count;

	seq_len = ring_size(seq);
	count = seq_len;
	tail[0] = 0;
	lis_len = 0;
	while (count--)
	{
		new_len = bsearch_new_len(seq, tail, lis_len, nth_val(seq, i));
		back[i] = tail[new_len - 1];
		tail[new_len] = i;
		if (new_len > lis_len)
			lis_len = new_len;
		i = (i + 1) % seq_len;
	}
	return (lis_len);
}

static int	*make_lis(t_ring *seq, int len, int *back, int k)
{
	int	*lis;
	int	i;

	lis = malloc(sizeof(*lis) * len);
	if (lis == NULL)
		exit(EXIT_FAILURE);
	i = len;
	while (i > 0)
	{
		lis[i - 1] = nth_val(seq, k);
		k = back[k];
		--i;
	}
	return (lis);
}
