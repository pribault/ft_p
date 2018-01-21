/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_enqueue_write_by_fd.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 14:09:48 by pribault          #+#    #+#             */
/*   Updated: 2018/01/21 14:16:52 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	client_enqueue_write_by_fd(t_client *client, int fd, t_msg *msg)
{
	t_towrite	towrite;

	if (!client || !msg)
		return ;
	towrite.fd = fd;
	towrite.data = *msg;
	ft_vector_add(client->write_queue, &towrite);
}
