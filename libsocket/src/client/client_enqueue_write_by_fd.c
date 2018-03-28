/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_enqueue_write_by_fd.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 14:09:48 by pribault          #+#    #+#             */
/*   Updated: 2018/03/28 11:37:20 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	client_enqueue_write_by_fd(t_client *client, int fd, t_msg *msg)
{
	t_towrite	towrite;

	towrite.fd = fd;
	towrite.data = *msg;
	ft_circ_buffer_enqueue(&client->write_queue, &towrite);
}
