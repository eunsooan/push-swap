/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ean <ean@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:20:21 by ean               #+#    #+#             */
/*   Updated: 2022/02/28 10:46:11 by ean              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INDEXING_H
# define INDEXING_H
# include "circular_buffer.h"

int	nth_val(const t_ring *r, const int n);
int	find_max_index_in_sorted_ring(const t_ring *r);
int	find_max_index(const t_ring *r);

#endif
