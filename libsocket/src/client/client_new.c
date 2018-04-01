/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 19:39:06 by pribault          #+#    #+#             */
/*   Updated: 2018/03/31 18:10:32 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_client	*client_new(void)
{
	t_client	*client;

	if (!(client = (t_client*)malloc(sizeof(t_client))))
		return (NULL);
	ft_bzero(client, sizeof(t_client));
	ft_circ_buffer_init(&client->write_queue, ALLOC_MALLOC, sizeof(t_towrite),
	CIRCULAR_BUFFER_SIZE);
	client->opt = CLIENT_RUNNING;
	client->timeout = (struct timeval){CLIENT_DEFAULT_TIMEOUT_S,
	CLIENT_DEFAULT_TIMEOUT_US};
	return (client);
}
