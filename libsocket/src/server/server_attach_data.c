/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_attach_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 10:47:12 by pribault          #+#    #+#             */
/*   Updated: 2018/03/28 11:30:11 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	server_attach_data(t_server *server, void *data)
{
	server->data = data;
}
