/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clients.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 16:28:35 by pribault          #+#    #+#             */
/*   Updated: 2018/02/02 19:15:45 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	add_client(void *server, void *client)
{
	t_cli	*cl;

	if (!(cl = server_get_data(server)))
		return ;
	if (server_get_client_fd(client))
		cl->fd = server_get_client_fd(client);
	if (((t_cli*)server_get_data(server))->opt & OPT_VERBOSE)
		ft_printf("client [%d] added\n", server_get_client_fd(client));
}

void	del_client(void *server, void *client)
{
	(void)client;
	if (((t_cli*)server_get_data(server))->opt & OPT_VERBOSE)
		ft_printf("client [%d] removed\n", server_get_client_fd(client));
}
