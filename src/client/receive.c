/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 20:30:31 by pribault          #+#    #+#             */
/*   Updated: 2018/03/16 06:56:40 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

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
	{NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{&recv_str, NULL, NULL, NULL, NULL, NULL, NULL},
	{&recv_state, &recv_file, NULL, NULL, NULL, NULL, NULL},
};

void	save_message(t_cli *client, t_header *ptr, size_t size)
{
	if (!client->data.ptr)
	{
		if (!(client->data.ptr = ft_memdup(ptr, size)))
			ft_error(2, ERROR_ALLOCATION, NULL);
		client->data.expected = ptr->size;
		client->data.size = size;
	}
	else if (client->data.size + size >= client->data.expected)
	{
		if (!(client->data.ptr = realloc(client->data.ptr,
			client->data.expected)))
			ft_error(2, ERROR_ALLOCATION, NULL);
		ft_memcpy(client->data.ptr + client->data.size, ptr,
		client->data.expected - client->data.size);
		client->data.size = client->data.expected;
	}
	else
	{
		if (!(client->data.ptr = realloc(client->data.ptr,
			client->data.size + size)))
			ft_error(2, ERROR_ALLOCATION, NULL);
		ft_memcpy(client->data.ptr + client->data.size, ptr, size);
		client->data.size += size;
	}
	ft_printf("%lu/%lu bytes\n", client->data.size, client->data.expected);
}

void	message_complete(t_cli *client, t_header *ptr, size_t size)
{
	if (client->opt & OPT_VERBOSE)
		ft_printf("message received of size %lu bytes\n", size);
	if (g_func[client->state][ptr->type])
		g_func[client->state][ptr->type](client, ptr, size);
	else
		ft_error(2, ERROR_UNEXPECTED_MSG, NULL);
	if (client->data.ptr)
	{
		free(client->data.ptr);
		ft_bzero(&client->data, sizeof(t_data));
	}
}

void	waiting_for_message(t_cli *client, t_header *ptr, size_t size)
{
	size_t	save;

	if (client->data.size + size >= client->data.expected)
	{
		save = client->data.expected - client->data.size;
		save_message(client, ptr, size);
		message_complete(client, client->data.ptr, client->data.expected);
		manage_received_msg(client, (void*)ptr + save, size - save);
	}
	else
		save_message(client, ptr, size);
}

void	manage_received_msg(t_cli *client, t_header *ptr, size_t size)
{
	if (client->data.ptr)
		waiting_for_message(client, ptr, size);
	else if (size >= sizeof(t_header))
	{
		if (ptr->size <= size)
		{
			message_complete(client, ptr, ptr->size);
			manage_received_msg(client, (void*)ptr + ptr->size,
			size - ptr->size);
		}
		else
			save_message(client, ptr, size);
	}
	else if (size)
		ft_error(2, ERROR_MSG_TOO_SMALL, NULL);
}
