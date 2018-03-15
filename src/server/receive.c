/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 13:17:45 by pribault          #+#    #+#             */
/*   Updated: 2018/03/15 22:51:54 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

/*
**	types:
**
**	- TYPE_STR
**	- TYPE_RAW
**	- TYPE_LS
**	- TYPE_CD
**	- TYPE_PWD
**	- TYPE_PUT
**	- TYPE_GET
**
**	states:
**
**	- STATE_NONE
**	- STATE_WAITING_FOR_STR
**	- STATE_WAITING_FOR_FILE
*/

static t_msg_handler	g_func[STATE_MAX][TYPE_MAX] =
{
	{NULL, NULL, &recv_ls, &recv_cd, &recv_pwd, &recv_put, &recv_get},
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL},
};

void	save_message(t_data *data, t_header *ptr, size_t size)
{
	if (!data->ptr)
	{
		if (!(data->ptr = ft_memdup(ptr, size)))
			ft_error(2, ERROR_ALLOCATION, NULL);
		data->expected = ptr->size;
		data->size = size;
	}
	else if (data->size + size >= data->expected)
	{
		if (!(data->ptr = realloc(data->ptr, data->expected)))
			ft_error(2, ERROR_ALLOCATION, NULL);
		ft_memcpy(data->ptr + data->size, ptr,
		data->expected - data->size);
	}
	else
	{
		if (!(data->ptr = realloc(data->ptr, data->size + size)))
			ft_error(2, ERROR_ALLOCATION, NULL);
		ft_memcpy(data->ptr + data->size, ptr, size);
		data->size += size;
	}
	ft_printf("message received %lu/%lu bytes\n",
	data->size, data->expected);
}

void	message_complete(t_server *server, void *client, t_header *ptr,
		size_t size)
{
	t_data	*data;

	if (!(data = server_client_get_data(client)))
		return (ft_error(2, ERROR_CUSTOM, "client data null, wtf ?!? ._."));
	if (server->opt & OPT_VERBOSE)
	{
		ft_printf("message received from [%d]:\n",
		server_get_client_fd(client));
		ft_printf("%lu\n", ptr->type);
	}
	if (g_func[data->state][ptr->type])
		g_func[data->state][ptr->type](server, client, ptr, size);
	else
		ft_error(2, ERROR_UNEXPECTED_MSG, NULL);
	if (data->ptr)
	{
		free(data->ptr);
		ft_bzero(data, sizeof(t_data));
	}
}

void	waiting_for_message(t_server *server, void *client, t_header *ptr,
		size_t size)
{
	t_data	*data;
	size_t	save;

	if (!(data = server_client_get_data(client)))
		return (ft_error(2, ERROR_CUSTOM, "client data null, wtf ?!? ._."));
	if (data->size + size >= data->expected)
	{
		save = data->expected - data->size;
		save_message(data, ptr, size);
		message_complete(server, client, data->ptr, data->expected);
		manage_received_msg(server, client, (void*)ptr + save, size - save);
	}
	else
		save_message(client, ptr, size);
}

void	manage_received_msg(t_server *server, void *client, t_header *ptr,
		size_t size)
{
	t_data	*data;

	if (!(data = server_client_get_data(client)))
		return (ft_error(2, ERROR_CUSTOM, "client data null, wtf ?!? ._."));
	if (data->ptr)
		waiting_for_message(server, data, ptr, size);
	else if (size >= sizeof(t_header))
	{
		if (ptr->size <= size)
		{
			message_complete(server, client, ptr, ptr->size);
			manage_received_msg(server, client, (void*)ptr + ptr->size,
			size - ptr->size);
		}
		else
			save_message(data, ptr, size);
	}
	else if (size)
		ft_error(2, ERROR_MSG_TOO_SMALL, NULL);
}
