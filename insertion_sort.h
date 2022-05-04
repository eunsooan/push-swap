/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertion_sort.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ean <ean@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 09:09:28 by ean               #+#    #+#             */
/*   Updated: 2022/02/28 09:09:59 by ean              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSERTION_SORT_H
# define INSERTION_SORT_H
# include "circular_buffer.h"

typedef struct s_cost
{
	int	src_r_count;
	int	dst_r_count;
	int	rr_count;
}	t_cost;

void	insertion_sort(t_ring *dst, t_ring *src);

#endif
