/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ean <ean@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:42:33 by ean               #+#    #+#             */
/*   Updated: 2022/02/25 15:02:47 by ean              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "moves.h"

static void	execute_swap(t_ring *a, t_ring *b, enum e_move mv);
static void	execute_push(t_ring *a, t_ring *b, enum e_move mv);
static void	execute_rotate(t_ring *a, t_ring *b, enum e_move mv);
static void	execute_reverse_rotate(t_ring *a, t_ring *b, enum e_move mv);

void	execute_move_n_times(t_ring *a, t_ring *b, enum e_move mv, int n)
{
	if (n == 0)
		return ;
	if (n < 0)
		n *= -1;
	if (mv == SA || mv == SB || mv == SS)
		while (n--)
			execute_swap(a, b, mv);
	else if (mv == PA || mv == PB)
		while (n--)
			execute_push(a, b, mv);
	else if (mv == RA || mv == RB || mv == RR)
		while (n--)
			execute_rotate(a, b, mv);
	else
		while (n--)
			execute_reverse_rotate(a, b, mv);
}

static void	execute_swap(t_ring *a, t_ring *b, enum e_move mv)
{
	int	top_element;
	int	second_element;

	if (a && (mv == SA || mv == SS) && ring_size(a) > 1)
	{
		top_element = ring_pop(a, FRONT);
		second_element = ring_pop(a, FRONT);
		ring_push(a, FRONT, top_element);
		ring_push(a, FRONT, second_element);
	}
	if (b && (mv == SB || mv == SS) && ring_size(b) > 1)
	{
		top_element = ring_pop(b, FRONT);
		second_element = ring_pop(b, FRONT);
		ring_push(b, FRONT, top_element);
		ring_push(b, FRONT, second_element);
	}
	if (mv == SA)
		write(STDOUT_FILENO, "sa\n", 3);
	else if (mv == SB)
		write(STDOUT_FILENO, "sb\n", 3);
	else
		write(STDOUT_FILENO, "ss\n", 3);
}

static void	execute_push(t_ring *a, t_ring *b, enum e_move mv)
{
	int	top_element;

	if (mv == PA && ring_size(b) > 0)
	{
		top_element = ring_pop(b, FRONT);
		ring_push(a, FRONT, top_element);
		write(STDOUT_FILENO, "pa\n", 3);
	}
	else if (mv == PB && ring_size(a) > 0)
	{
		top_element = ring_pop(a, FRONT);
		ring_push(b, FRONT, top_element);
		write(STDOUT_FILENO, "pb\n", 3);
	}
}

static void	execute_rotate(t_ring *a, t_ring *b, enum e_move mv)
{
	if (a && (mv == RA || mv == RR) && ring_size(a) > 1)
		ring_push(a, BACK, ring_pop(a, FRONT));
	if (b && (mv == RB || mv == RR) && ring_size(b) > 1)
		ring_push(b, BACK, ring_pop(b, FRONT));
	if (mv == RA)
		write(STDOUT_FILENO, "ra\n", 3);
	else if (mv == RB)
		write(STDOUT_FILENO, "rb\n", 3);
	else
		write(STDOUT_FILENO, "rr\n", 3);
}

static void	execute_reverse_rotate(t_ring *a, t_ring *b, enum e_move mv)
{
	if (a && (mv == RRA || mv == RRR) && ring_size(a) > 1)
		ring_push(a, FRONT, ring_pop(a, BACK));
	if (b && (mv == RRB || mv == RRR) && ring_size(b) > 1)
		ring_push(b, FRONT, ring_pop(b, BACK));
	if (mv == RRA)
		write(STDOUT_FILENO, "rra\n", 4);
	else if (mv == RRB)
		write(STDOUT_FILENO, "rrb\n", 4);
	else
		write(STDOUT_FILENO, "rrr\n", 4);
}
