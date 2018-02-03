/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_set_timeout.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 16:06:27 by pribault          #+#    #+#             */
/*   Updated: 2018/02/02 16:07:43 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	server_set_timeout(t_server *server, struct timeval timeout)
{
	if (!server)
		return ;
	server->timeout = timeout;
}
