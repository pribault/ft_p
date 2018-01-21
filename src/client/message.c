/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 16:32:55 by pribault          #+#    #+#             */
/*   Updated: 2018/01/21 20:41:14 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

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
			return (error(1, 1, NULL));
		i = ft_arraylen(array);
		while (--i != (size_t)-1)
			treat_command(server_get_data(server), array[i]);
		ft_free_array((void**)array, ft_arraylen(array) + 1);
		free(s);
	}
	else
	{
		ft_printf("message received from [%d]:\n",
		server_get_client_fd(client));
		write(1, msg->ptr, msg->size);
	}
}

void	msg_send(void *server, void *client, t_msg *msg)
{
	(void)server;
	(void)client;
	(void)msg;
	ft_printf("message sended to [%d]\n", server_get_client_fd(client));
}
