/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_set_queue_max.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 14:14:59 by pribault          #+#    #+#             */
/*   Updated: 2018/03/28 11:35:41 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		server_set_queue_max(t_server *server, int max)
{
	if (max < 0)
		return (0);
	server->queue_max = max;
	return (1);
}
