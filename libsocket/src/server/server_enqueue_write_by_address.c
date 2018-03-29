/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_enqueue_write_by_address.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 18:02:08 by pribault          #+#    #+#             */
/*   Updated: 2018/03/29 18:04:37 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	server_enqueue_write_by_address(t_server *server,
		struct sockaddr *address, t_msg *msg)
{
	t_client	client;

	ft_bzero(&client, sizeof(t_client));
	client.addr = *address;
	server_enqueue_write(server, &client, msg);
}
