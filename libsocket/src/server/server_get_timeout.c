/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_get_timeout.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 16:06:27 by pribault          #+#    #+#             */
/*   Updated: 2018/02/02 16:08:50 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

struct timeval	server_get_timeout(t_server *server)
{
	return ((server) ? server->timeout : (struct timeval){0, 0});
}
