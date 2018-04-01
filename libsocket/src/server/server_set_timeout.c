/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_set_timeout.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 11:21:19 by pribault          #+#    #+#             */
/*   Updated: 2018/03/28 11:27:56 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	server_set_timeout(t_server *server,
		uint64_t seconds, uint64_t micro_seconds)
{
	server->timeout.tv_sec = seconds;
	server->timeout.tv_usec = micro_seconds;
}
