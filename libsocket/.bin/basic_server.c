/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_server.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 21:23:23 by pribault          #+#    #+#             */
/*   Updated: 2018/01/21 14:18:56 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"
#include "libft.h"

void	treat_command(t_server *server, void *cmd, size_t size)
{
	char	**array;
	size_t	len;

	((char*)cmd)[size] = '\0';
	if ((array = ft_multisplit(cmd, "\a\b\t\n\v\f\r ")))
	{
		len = ft_arraylen(array);
		if (len == 1 && !ft_strcmp(array[0], "exit"))
		{
			ft_printf("goodbye !\n");
			exit(0);
		}
		else if (len == 3 && !ft_strcmp(array[0], "connect"))
			server_connect(server, array[1], array[2]);
		ft_free_array((void**)array, len + 1);
	}
	free(cmd);
}

void	client_add(t_server *server, t_client *client)
{
	t_msg	msg;

	msg.ptr = ft_joinf("client [%s] added\n", server_get_client_address(client));
	msg.size = ft_strlen(msg.ptr);
	server_enqueue_write_by_fd(server, 1, &msg);
}

void	client_del(t_server *server, t_client *client)
{
	t_msg	msg;

	msg.ptr = ft_joinf("client [%s] deleted\n", server_get_client_address(client));
	msg.size = ft_strlen(msg.ptr);
	server_enqueue_write_by_fd(server, 1, &msg);
}

void	msg_recv(t_server *server, t_client *client, t_msg *msg)
{
	t_msg	new_msg;

	new_msg.ptr = ft_joinf("message of size %d received from [%s]\n",
	msg->size, server_get_client_address(client));
	new_msg.size = ft_strlen(new_msg.ptr);
	server_enqueue_write_by_fd(server, 1, &new_msg);
	if (server_get_client_fd(client) == 0)
		treat_command(server, ft_memdup(msg->ptr, msg->size + 1), msg->size);
}

void	msg_send(t_server *server, t_client *client, t_msg *msg)
{
	t_msg	new_msg;

	if (server_get_client_fd(client) <= 1)
		return ;
	new_msg.ptr = ft_joinf("message of size %d sended to [%s]\n", msg->size,
		server_get_client_address(client));
	new_msg.size = ft_strlen(new_msg.ptr);
	server_enqueue_write_by_fd(server, 1, &new_msg);
}

int	main(int argc, char **argv)
{
	t_server	*server;

	if (argc != 2)
		return (1);
	server = server_new();
	server_set_queue_max(server, 1);
	if (!server_start(server, TCP, argv[1]))
	{
		ft_printf("cannot bind to %s\n", argv[1]);
		return (1);
	}
	server_set_callback(server, SERVER_CLIENT_ADD_CB, &client_add);
	server_set_callback(server, SERVER_CLIENT_DEL_CB, &client_del);
	server_set_callback(server, SERVER_MSG_RECV_CB, &msg_recv);
	server_set_callback(server, SERVER_MSG_SEND_CB, &msg_send);
	server_add_client_by_fd(server, 0);
	while (1)
	{
		server_poll_events(server);
	}
	return (0);
}
