/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_get_client_address.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 13:33:21 by pribault          #+#    #+#             */
/*   Updated: 2018/03/29 18:00:31 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

struct sockaddr_storage	*server_get_client_address(t_client *client)
{
	return (&client->addr);
}
