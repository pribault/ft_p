/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_get_incoming_message.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 13:46:42 by pribault          #+#    #+#             */
/*   Updated: 2018/01/21 13:50:44 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	client_get_incoming_message(t_client *client, int *n_evts)
{
	static char		buffer[READ_BUFFER_SIZE];
	int				ret;
	static t_msg	msg;

	if (*n_evts < 1)
		return ;
	if ((ret = read(client->sockfd, &buffer, READ_BUFFER_SIZE)) > 0)
	{
		if (client->msg_recv)
		{
			msg.ptr = &buffer;
			msg.size = ret;
			client->msg_recv(client, &msg);
		}
	}
	else if (!ret)
		client_disconnect(client);
}
