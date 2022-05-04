/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circular_buffer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ean <ean@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 12:31:43 by ean               #+#    #+#             */
/*   Updated: 2022/02/28 10:47:50 by ean              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "circular_buffer.h"

t_ring	*create_ring(const int item_count)
{
	t_ring	*new;

	if (item_count <= 0)
		exit(EXIT_FAILURE);
	new = malloc(sizeof(*new));
	if (new == NULL)
		exit(EXIT_FAILURE);
	new->capacity = item_count + 1;
	new->arr = malloc(sizeof(*(new->arr)) * (item_count + 1));
	if (new->arr == NULL)
	{
		free(new);
		exit(EXIT_FAILURE);
	}
	new->front = 0;
	new->back = 0;
	return (new);
}

void	destroy_ring(t_ring *buf)
{
	if (buf)
		free(buf->arr);
	free(buf);
}

int	ring_size(const t_ring *buf)
{
	return ((buf->back + buf->capacity - buf->front) % buf->capacity);
}

void	ring_push(t_ring *buf, const enum e_end where, const int item)
{
	if (ring_size(buf) == buf->capacity - 1)
	{
		write(STDERR_FILENO, "BUFFER FULL\n", 12);
		destroy_ring(buf);
		exit(EXIT_FAILURE);
	}
	if (where == FRONT)
	{
		buf->arr[buf->front] = item;
		buf->front = (buf->front + buf->capacity - 1) % buf->capacity;
	}
	else
	{
		buf->back = (buf->back + 1) % buf->capacity;
		buf->arr[buf->back] = item;
	}
}

int	ring_pop(t_ring *buf, const enum e_end where)
{
	int	ret;

	if (ring_size(buf) == 0)
	{
		write(STDERR_FILENO, "BUFFER EMPTY\n", 13);
		destroy_ring(buf);
		exit(EXIT_FAILURE);
	}
	if (where == FRONT)
	{
		buf->front = (buf->front + 1) % buf->capacity;
		ret = buf->arr[buf->front];
	}
	else
	{
		ret = buf->arr[buf->back];
		buf->back = (buf->back + buf->capacity - 1) % buf->capacity;
	}
	return (ret);
}
