/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_enqueue_write.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 09:45:27 by pribault          #+#    #+#             */
/*   Updated: 2018/01/20 09:49:24 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	server_enqueue_write(t_server *server, t_client *client,
		t_msg *msg)
{
	t_towrite	towrite;

	if (!server || !client || !msg)
		return ;
	towrite.client = *client;
	towrite.data = *msg;
	ft_vector_add(server->write_queue, &towrite);
}
