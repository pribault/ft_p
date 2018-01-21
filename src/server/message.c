/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 16:32:55 by pribault          #+#    #+#             */
/*   Updated: 2018/01/21 20:23:03 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	msg_recv(void *server, void *client, t_msg *msg)
{
	char	*s;
	int		fd;

	fd = server_get_client_fd(client);
	if (fd == 0)
	{
		if (!(s = ft_memdup(msg->ptr, msg->size)))
			return (error(1, 1, NULL));
		s[msg->size - 1] = '\0';
		treat_command(server_get_data(server), s);
		free(s);
	}
	else
	{
		ft_printf("message received from [%d]:\n",
		server_get_client_fd(client));
		ft_memdump(msg->ptr, msg->size);
	}
}

void	msg_send(void *server, void *client, t_msg *msg)
{
	(void)server;
	(void)client;
	(void)msg;
	ft_printf("message sended to [%d]\n", server_get_client_fd(client));
}
