/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_disconnect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 15:17:37 by pribault          #+#    #+#             */
/*   Updated: 2018/03/28 11:37:14 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	client_disconnect(t_client *client)
{
	if (!(client->opt & CLIENT_CONNECTED))
		return ;
	close(client->sockfd);
	client->opt &= ~CLIENT_CONNECTED;
	if (client->disconnect)
		client->disconnect(client);
}
