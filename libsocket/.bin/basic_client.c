/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_client.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 13:58:24 by pribault          #+#    #+#             */
/*   Updated: 2018/01/21 14:23:30 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"
#include "libft.h"

void	connected(t_client *client)
{
	t_msg	msg;

	msg.ptr = ft_joinf("connected\n");
	msg.size = ft_strlen(msg.ptr);
	client_enqueue_write_by_fd(client, 1, &msg);
}

void	disconnected(t_client *client)
{
	t_msg	msg;

	msg.ptr = ft_joinf("disconnected\n");
	msg.size = ft_strlen(msg.ptr);
	client_enqueue_write_by_fd(client, 1, &msg);
}

void	msg_recv(t_client *client, t_msg *msg)
{
	t_msg	new_msg;

	new_msg.ptr = ft_joinf("message of size %d received\n",
	msg->size);
	new_msg.size = ft_strlen(new_msg.ptr);
	client_enqueue_write_by_fd(client, 1, &new_msg);
}

void	msg_send(t_client *client, int fd, t_msg *msg)
{
	t_msg	new_msg;

	(void)fd;
	if (fd <= 2)
		return ;
	new_msg.ptr = ft_joinf("message of size %d sended\n", msg->size);
	new_msg.size = ft_strlen(new_msg.ptr);
	client_enqueue_write_by_fd(client, 1, &new_msg);
}

int	main(int argc, char **argv)
{
	t_client	*client;

	if (argc != 3)
		return (1);
	client = client_new();
	client_set_callback(client, CLIENT_CONNECT_CB, &connected);
	client_set_callback(client, CLIENT_DISCONNECT_CB, &disconnected);
	client_set_callback(client, CLIENT_MSG_RECV_CB, &msg_recv);
	client_set_callback(client, CLIENT_MSG_SEND_CB, &msg_send);
	if (!client_connect(client, TCP, argv[1], argv[2]))
		return (1);
	while (1)
	{
		client_poll_events(client);
	}
	return (0);
}
