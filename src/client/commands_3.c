/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 21:35:41 by pribault          #+#    #+#             */
/*   Updated: 2018/03/31 22:43:25 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	send_mv_request(t_cli *client, char **cmds, size_t len)
{
	size_t	l[2];
	char	move[2][FILE_NAME_MAX_SIZE];

	if ((l[0] = ft_strlen(cmds[1])) >= FILE_NAME_MAX_SIZE)
		return (ft_error(2, ERROR_FILE_NAME_TOO_LONG, cmds[1]));
	if ((l[1] = ft_strlen(cmds[2])) >= FILE_NAME_MAX_SIZE)
		return (ft_error(2, ERROR_FILE_NAME_TOO_LONG, cmds[2]));
	ft_memcpy(&move[0][0], cmds[1], l[0]);
	move[0][l[0]] = '\0';
	ft_memcpy(&move[1][0], cmds[2], l[1]);
	move[1][l[1]] = '\0';
	if (len == 3)
		enqueue_msg(client, &move, 2 * FILE_NAME_MAX_SIZE, TYPE_MV);
	else
		return (ft_error(2, ERROR_MV_PARAMS, NULL));
	client->state = STATE_WAITING_FOR_STR;
}
