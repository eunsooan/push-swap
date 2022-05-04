/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ean <ean@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 16:38:27 by ean               #+#    #+#             */
/*   Updated: 2022/02/28 11:02:07 by ean              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "circular_buffer.h"
#include "moves.h"
#include "lics.h"
#include "insertion_sort.h"
#include "indexing.h"
#include "sort_three_or_less.h"

static void	process_input(t_ring *stack, int item_count, char **str_arr);
static int	is_not_number(const char *str);
static int	convert_str_to_int(const char *str, int *number);
static int	has_duplicate(const t_ring *stack, const int number);

int	main(int argc, char *argv[])
{
	t_ring	*stack_a;
	t_ring	*stack_b;

	if (argc == 1)
		return (0);
	stack_a = create_ring(argc - 1);
	stack_b = create_ring(argc - 1);
	process_input(stack_a, argc - 1, &argv[1]);
	if (ring_size(stack_a) <= 3)
		sort_three_or_less(stack_a);
	else
	{
		filter_out_misplaced_elements(stack_a, stack_b);
		insertion_sort(stack_a, stack_b);
	}
	destroy_ring(stack_a);
	destroy_ring(stack_b);
	return (0);
}

static void	process_input(t_ring *stack, int item_count, char **str_arr)
{
	int	i;
	int	number;

	i = 0;
	while (i < item_count)
	{
		if (is_not_number(str_arr[i]))
			break ;
		if (!convert_str_to_int(str_arr[i], &number))
			break ;
		if (has_duplicate(stack, number))
			break ;
		ring_push(stack, BACK, number);
		++i;
	}
	if (i < item_count)
	{
		write(STDERR_FILENO, "Error\n", 6);
		destroy_ring(stack);
		exit(EXIT_FAILURE);
	}
}

static int	is_not_number(const char *str)
{
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		++str;
	if (*str == '+' || *str == '-')
		++str;
	if (*str == 0)
		return (1);
	while ('0' <= *str && *str <= '9')
		++str;
	if (*str)
		return (1);
	return (0);
}

static int	convert_str_to_int(const char *str, int *number)
{
	int	multiplier;

	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		++str;
	multiplier = -1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			multiplier = 1;
		++str;
	}
	*number = 0;
	while (*str)
	{
		if (*number < *number * 10 - (*str - '0'))
			return (0);
		*number = *number * 10 - (*str - '0');
		++str;
	}
	if (multiplier == -1 && 0 - *number < 0)
		return (0);
	*number *= multiplier;
	return (1);
}

static int	has_duplicate(const t_ring *stack, const int number)
{
	int	i;
	int	size;

	size = ring_size(stack);
	if (size == 0)
		return (0);
	i = 0;
	while (i < size)
	{
		if (nth_val(stack, i) == number)
			return (1);
		++i;
	}
	return (0);
}
