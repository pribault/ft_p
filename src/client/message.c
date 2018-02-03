/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 16:32:55 by pribault          #+#    #+#             */
/*   Updated: 2018/02/03 14:00:12 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	enqueue_msg(t_client *client, void *data, size_t size, uint8_t type)
{
	static t_msg	msg;

	if (!(msg.ptr = malloc(sizeof(t_header) + size)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	msg.size = sizeof(t_header) + size;
	((t_header*)msg.ptr)->type = type;
	((t_header*)msg.ptr)->size = msg.size;
	ft_memcpy(msg.ptr + sizeof(t_header), data, size);
	server_enqueue_write_by_fd(client->server, client->fd, &msg);
}

void	msg_recv(void *server, void *client, t_msg *msg)
{
	size_t	i;
	char	**array;
	char	*s;
	int		fd;

	fd = server_get_client_fd(client);
	if (fd == 0)
	{
		if (!(s = ft_memdup(msg->ptr, msg->size)) ||
			(s[msg->size - 1] = '\0') ||
			!(array = ft_multisplit(s, "\n")))
			return (ft_error(2, ERROR_ALLOCATION, NULL));
		i = ft_arraylen(array);
		while (--i != (size_t)-1)
			treat_command(server_get_data(server), array[i]);
		ft_free_array((void**)array, ft_arraylen(array));
		free(s);
	}
	else
		manage_received_msg(server_get_data(server), msg->ptr, msg->size);
}

void	msg_send(void *server, void *client, t_msg *msg)
{
	(void)client;
	free(msg->ptr);
	if (server_get_client_fd(client) != 1 &&
		((t_client*)server_get_data(server))->opt & OPT_VERBOSE)
		ft_printf("message sended to [%d]\n",
		server_get_client_fd(client));
}
