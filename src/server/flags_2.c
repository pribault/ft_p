/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 16:17:46 by pribault          #+#    #+#             */
/*   Updated: 2018/02/02 16:18:28 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	get_max(char **args, int n_params, t_server *server)
{
	(void)n_params;
	server_set_queue_max(server->server, atoi(args[0]));
}

void	get_timeout(char **args, int n_params, t_server *server)
{
	(void)n_params;
	server_set_timeout(server->server,
	(struct timeval){ft_atou(args[0]), ft_atou(args[1])});
}
