/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_enqueue_write_by_fd.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 09:59:57 by pribault          #+#    #+#             */
/*   Updated: 2018/01/20 10:01:26 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	server_enqueue_write_by_fd(t_server *server, int fd, t_msg *msg)
{
	t_client	client;

	ft_bzero(&client, sizeof(t_client));
	client.fd = fd;
	server_enqueue_write(server, &client, msg);
}
