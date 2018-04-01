/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_delete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 08:37:07 by pribault          #+#    #+#             */
/*   Updated: 2018/03/28 11:30:55 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	server_delete(t_server **server)
{
	ft_vector_del(&(*server)->clients);
	ft_circ_buffer_del(&(*server)->write_queue);
	free(*server);
}
