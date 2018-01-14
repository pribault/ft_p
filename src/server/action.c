/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 18:29:13 by pribault          #+#    #+#             */
/*   Updated: 2018/01/14 21:29:54 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	send_raw_text(t_server *server, t_client *client, char *s)
{
	t_header	header;

	header.type = TYPE_RAW_TEXT;
	header.size = ft_strlen(s);
	enqueue_write(server, client->fd, &header, sizeof(t_header));
	enqueue_write(server, client->fd, s, header.size);
}

void	get_raw_text(t_server *server, t_client *client, void *msg,
		size_t size)
{
	(void)client;
	enqueue_putendl(server, 1, msg, size);
}

void	do_pwd(t_server *server, t_client *client, void *msg, size_t size)
{
	char	*s;

	(void)msg;
	(void)size;
	if (!(s = ft_joinf("/%s", client->dir + ft_strlen(server->root))))
		error(1, 1, NULL);
	send_raw_text(server, client, s);
	free(s);
}
