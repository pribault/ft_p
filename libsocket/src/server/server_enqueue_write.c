/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_enqueue_write.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 09:45:27 by pribault          #+#    #+#             */
/*   Updated: 2018/03/28 11:31:04 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	server_enqueue_write(t_server *server, t_client *client,
		t_msg *msg)
{
	t_towrite	towrite;

	towrite.client = *client;
	towrite.data = *msg;
	ft_circ_buffer_enqueue(&server->write_queue, &towrite);
}
