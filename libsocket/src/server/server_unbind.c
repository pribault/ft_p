/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_unbind.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 10:46:26 by pribault          #+#    #+#             */
/*   Updated: 2018/01/21 10:55:33 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	server_unbind(t_server *server)
{
	if (!server || !(server->opt & SERVER_BIND))
		return ;
	server->opt &= ~SERVER_BIND;
	close(server->sockfd);
	return ;
}
