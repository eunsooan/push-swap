/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circular_buffer.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ean <ean@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:53:52 by ean               #+#    #+#             */
/*   Updated: 2022/02/28 10:47:36 by ean              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CIRCULAR_BUFFER_H
# define CIRCULAR_BUFFER_H
# include <stdlib.h>

typedef struct s_ring
{
	int	capacity;
	int	*arr;
	int	front;
	int	back;
}	t_ring;

enum e_end
{
	FRONT,
	BACK,
};

t_ring	*create_ring(const int item_count);
void	destroy_ring(t_ring *buf);
int		ring_size(const t_ring *buf);
void	ring_push(t_ring *buf, const enum e_end where, const int item);
int		ring_pop(t_ring *buf, const enum e_end where);

#endif
