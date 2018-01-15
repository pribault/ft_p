/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 21:09:43 by pribault          #+#    #+#             */
/*   Updated: 2018/01/15 08:39:28 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	execute(t_client *client, t_header *msg)
{
	if (msg->type < TYPE_MAX)
	{
		if (g_state_machine[client->state][msg->type])
			g_state_machine[client->state][msg->type](client,
				(void*)msg + sizeof(t_header), msg->size);
		else
		{
			g_state_machine[client->state][0](client,
				(void*)msg + sizeof(t_header), msg->size);
			error(102, 0, &msg->type);
		}
	}
	else
		error(101, 0, NULL);
}

void	enter_wait_state(t_client *client, void *data, size_t size)
{
	t_waiting	waiting;

	waiting.state = client->state;
	waiting.size = size;
	if (!(waiting.data = ft_memdup(data, size)))
		error(1, 1, NULL);
	waiting.exp = waiting.data->size + sizeof(t_header);
	if (!(client->data = ft_memdup(&waiting, sizeof(t_waiting))))
		error(1, 1, NULL);
	client->state = STATE_WAITING;
}

void	wait_state(t_client *client, void *data, size_t size)
{
	t_waiting	*waiting;

	waiting = client->data;
	if (waiting->size + size < waiting->exp)
	{
		if (!(waiting->data = realloc(waiting->data, waiting->size + size)))
			error(1, 1, NULL);
		ft_memcpy(waiting->data + waiting->size, data, size);
		waiting->size += size;
	}
	else
	{
		if (!(waiting->data = realloc(waiting->data, waiting->exp)))
			error(1, 1, NULL);
		ft_memcpy((void*)waiting->data + waiting->size, data,
			waiting->exp - waiting->size);
		client->state = waiting->state;
		client->data = NULL;
		execute(client, waiting->data);
		treat_message(client, data + waiting->exp - waiting->size,
			size + waiting->size - waiting->exp);
		free(waiting);
	}
}

void	treat_message(t_client *client, t_header *msg, size_t size)
{
	if (client->state == STATE_WAITING)
		wait_state(client, msg, size);
	else if (size >= sizeof(t_header))
	{
		if (msg->size <= size - sizeof(t_header))
			execute(client, msg);
		else if (msg->type < TYPE_MAX)
			enter_wait_state(client, msg, size);
		else
			error(102, 0, &msg->type);
	}
	else if (size != 0)
		error(100, 0, NULL);
	free(msg);
}
