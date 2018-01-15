/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 20:40:15 by pribault          #+#    #+#             */
/*   Updated: 2018/01/15 20:47:10 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	send_pwd_request(t_client *client, char **cmd, size_t size)
{
	t_header	header;

	(void)cmd;
	if (size != 1)
		return (error(202, 0, NULL));
	header.type = TYPE_PWD;
	header.size = 0;
	enqueue_write(client, client->socket, &header, sizeof(t_header));
	client->state = STATE_WAITING_FOR_RAW_TEXT;
}

void	send_ls_request(t_client *client, char **cmd, size_t size)
{
	t_header	header;
	char		*s;

	if (size == 1)
		return (error(203, 0, NULL));
	if (!(s = ft_implode(cmd, ' ')))
		error(1, 1, NULL);
	header.type = TYPE_LS;
	header.size = ft_strlen(s);
	enqueue_write(client, client->socket, &header, sizeof(t_header));
	enqueue_write(client, client->socket, s, header.size);
	client->state = STATE_WAITING_FOR_RAW_TEXT;
}
