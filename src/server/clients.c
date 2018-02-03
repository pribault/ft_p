/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clients.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 16:28:35 by pribault          #+#    #+#             */
/*   Updated: 2018/02/03 13:48:37 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	add_client(void *server, void *client)
{
	t_data		data;
	t_server	*srv;

	if (!(srv = server_get_data(server)))
		return ;
	if (((t_server*)server_get_data(server))->opt & OPT_VERBOSE)
		ft_printf("client [%d] added\n", server_get_client_fd(client));
	ft_bzero(&data, sizeof(t_data));
	data.pwd = ft_strdup(srv->root);
	server_client_attach_data(client, ft_memdup(&data, sizeof(t_data)));
}

void	del_client(void *server, void *client)
{
	t_data		*data;
	t_server	*srv;

	if (!(srv = server_get_data(server)))
		return ;
	if (((t_server*)server_get_data(server))->opt & OPT_VERBOSE)
		ft_printf("client [%d] removed\n", server_get_client_fd(client));
	if (!(data = server_client_get_data(client)))
		return ;
	free(data->pwd);
	free(data);
}
