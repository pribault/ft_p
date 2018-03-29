/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_find_client_by_address.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 17:26:20 by pribault          #+#    #+#             */
/*   Updated: 2018/03/29 17:31:30 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_client	*server_find_client_by_address(t_server *server,
			struct sockaddr *addr)
{
	t_client	*client;
	t_vector	*vector;
	size_t		i;

	i = (size_t)-1;
	vector = &server->clients;
	while (++i < vector->n)
		if (!(client = ft_vector_get(vector, i)))
			return (NULL);
		else if (!memcmp(&client->addr, addr, sizeof(struct sockaddr)))
			return (client);
	return (NULL);
}
