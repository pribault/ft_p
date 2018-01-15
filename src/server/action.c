/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 18:29:13 by pribault          #+#    #+#             */
/*   Updated: 2018/01/15 21:47:07 by pribault         ###   ########.fr       */
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
	t_header	header;
	t_return	ret;
	char		*s;

	(void)msg;
	(void)size;
	if (!(s = ft_joinf("/%s", client->dir + ft_strlen(server->root))))
		error(1, 1, NULL);
	header.type = TYPE_RAW_TEXT;
	header.size = ft_strlen(s) + sizeof(t_return);
	ret = RETURN_SUCCESS;
	enqueue_write(server, client->fd, &header, sizeof(t_header));
	enqueue_write(server, client->fd, &ret, sizeof(t_return));
	enqueue_write(server, client->fd, s, header.size - sizeof(t_return));
	free(s);
}

void	do_ls(t_server *server, t_client *client, void *msg, size_t size)
{
	char		**array;
	t_header	header;
	t_return	ret;
	char		*s[2];

	if (!(s[0] = malloc(size + 1)))
		error(1, 1, NULL);
	ft_memcpy(s[0], msg, size);
	s[0][size] = '\0';
	if (!(array = ft_multisplit(s[0], WHITESPACES)) ||
		!(s[1] = ft_execute("/bin/ls", array, server->env)))
		error(1, 1, NULL);
	header.type = TYPE_RAW_TEXT;
	header.size = ft_strlen(s[1]) + sizeof(t_return);
	ret = RETURN_SUCCESS;
	enqueue_write(server, client->fd, &header, sizeof(t_header));
	enqueue_write(server, client->fd, &ret, sizeof(t_return));
	enqueue_write(server, client->fd, s[1], header.size - sizeof(t_return));
	ft_free_array((void**)array, ft_arraylen(array));
	free(s[0]);
	free(s[1]);
}
