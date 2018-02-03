/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_delete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 08:37:07 by pribault          #+#    #+#             */
/*   Updated: 2018/01/19 08:40:08 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	server_delete(t_server **server)
{
	if (!server || !(*server))
		return ;
	ft_vector_del(&(*server)->clients);
	ft_vector_del(&(*server)->write_queue);
	free(*server);
}
