/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 16:32:55 by pribault          #+#    #+#             */
/*   Updated: 2018/02/03 15:37:28 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_msg	new_msg(void *ptr, size_t size)
{
	return ((t_msg){ptr, size});
}

void	enqueue_msg(t_server *server, void *client, t_msg msg, uint8_t type)
{
	static t_msg	new_msg;

	if (!(new_msg.ptr = malloc(sizeof(t_header) + msg.size)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	new_msg.size = sizeof(t_header) + msg.size;
	((t_header*)new_msg.ptr)->type = type;
	((t_header*)new_msg.ptr)->size = new_msg.size;
	ft_memcpy(new_msg.ptr + sizeof(t_header), msg.ptr, msg.size);
	server_enqueue_write_by_fd(server->server, server_get_client_fd(client),
	&new_msg);
}

void	msg_recv(void *server, void *client, t_msg *msg)
{
	char	*s;
	int		fd;

	fd = server_get_client_fd(client);
	if (fd == 0)
	{
		if (!(s = ft_memdup(msg->ptr, msg->size)))
			return (ft_error(2, ERROR_ALLOCATION, NULL));
		s[msg->size - 1] = '\0';
		treat_command(server_get_data(server), s);
		free(s);
	}
	else
		manage_received_msg(server_get_data(server), client, msg->ptr,
		msg->size);
}

void	msg_send(void *server, void *client, t_msg *msg)
{
	(void)client;
	(void)msg;
	if (((t_server*)server_get_data(server))->opt & OPT_VERBOSE)
		ft_printf("message of size %lu sended to [%d]\n", msg->size,
		server_get_client_fd(client));
}
