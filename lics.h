/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lics.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ean <ean@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 14:50:35 by ean               #+#    #+#             */
/*   Updated: 2022/02/24 11:30:57 by ean              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LICS_H
# define LICS_H
# include "circular_buffer.h"

void	filter_out_misplaced_elements(t_ring *stack, t_ring *bin);

#endif
