/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_get_client_address.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 13:33:21 by pribault          #+#    #+#             */
/*   Updated: 2018/03/28 11:31:19 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

char	*server_get_client_address(t_client *client)
{
	return (inet_ntoa(((struct sockaddr_in*)&client->addr)->sin_addr));
}
