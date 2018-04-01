/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clients.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 16:28:35 by pribault          #+#    #+#             */
/*   Updated: 2018/03/31 12:26:57 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	add_client(void *server, void *client)
{
	t_data	data;
	t_serv	*srv;

	if (!(srv = server_get_data(server)))
		return ;
	if (((t_serv*)server_get_data(server))->opt & OPT_VERBOSE)
		ft_printf("client [%d] added\n", server_get_client_fd(client));
	ft_bzero(&data, sizeof(t_data));
	data.pwd = ft_strdup(srv->root);
	server_client_attach_data(client, ft_memdup(&data, sizeof(t_data)));
}

void	del_client(void *server, void *client)
{
	t_data	*data;
	t_serv	*srv;

	if (!(srv = server_get_data(server)))
		return ;
	if (srv->opt & OPT_VERBOSE)
		ft_printf("client [%d] removed\n", server_get_client_fd(client));
	if (!(data = server_client_get_data(client)))
		return ;
	free(data->pwd);
	free(data);
}
