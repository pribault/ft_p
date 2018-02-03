/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 19:39:06 by pribault          #+#    #+#             */
/*   Updated: 2018/01/21 13:37:22 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_client	*client_new(void)
{
	t_client	*client;

	if (!(client = (t_client*)malloc(sizeof(t_client))))
		return (NULL);
	ft_bzero(client, sizeof(t_client));
	if (!(client->write_queue = ft_vector_new(sizeof(t_towrite), 0)))
	{
		free(client);
		return (NULL);
	}
	client->opt = CLIENT_RUNNING;
	client->timeout = (struct timeval){CLIENT_DEFAULT_TIMEOUT_S,
	CLIENT_DEFAULT_TIMEOUT_US};
	return (client);
}
