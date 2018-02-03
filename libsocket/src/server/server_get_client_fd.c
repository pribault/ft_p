/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_get_client_fd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 22:30:38 by pribault          #+#    #+#             */
/*   Updated: 2018/01/19 22:34:14 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		server_get_client_fd(t_client *client)
{
	return ((client) ? client->fd : -1);
}
