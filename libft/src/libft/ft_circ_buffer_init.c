/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_circ_buffer_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 19:37:34 by pribault          #+#    #+#             */
/*   Updated: 2018/03/27 08:48:20 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_circ_buffer_init(t_circ_buffer *buffer, uint64_t type_size,
		uint64_t n_elements)
{
	buffer->write_idx = 0;
	buffer->read_idx = 0;
	buffer->type = type_size;
	buffer->elems = n_elements + 1;
	buffer->n = 0;
	if (!(buffer->ptr = malloc(type_size * n_elements)))
		ft_error(2, ERROR_ALLOCATION, NULL);
}
