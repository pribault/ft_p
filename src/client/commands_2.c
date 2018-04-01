/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 13:10:29 by pribault          #+#    #+#             */
/*   Updated: 2018/03/31 21:57:00 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	quit(t_cli *client, char **cmds, size_t len)
{
	(void)client;
	(void)cmds;
	if (len != 1)
		ft_error(2, ERROR_EXIT_PARAMS, NULL);
	exit(0);
}

void	send_ls_request(t_cli *client, char **cmds, size_t len)
{
	if (len == 1)
		enqueue_msg(client, ".", 1, TYPE_LS);
	else if (len == 2)
		enqueue_msg(client, cmds[1], ft_strlen(cmds[1]), TYPE_LS);
	else
		return (ft_error(2, ERROR_LS_PARAMS, NULL));
	client->state = STATE_WAITING_FOR_STR;
}

void	send_cd_request(t_cli *client, char **cmds, size_t len)
{
	if (len == 1)
		enqueue_msg(client, "/", 1, TYPE_CD);
	else if (len == 2)
		enqueue_msg(client, cmds[1], ft_strlen(cmds[1]), TYPE_CD);
	else
		return (ft_error(2, ERROR_CD_PARAMS, NULL));
	client->state = STATE_WAITING_FOR_STR;
}

void	send_pwd_request(t_cli *client, char **cmds, size_t len)
{
	(void)cmds;
	if (len == 1)
		enqueue_msg(client, NULL, 0, TYPE_PWD);
	else
		return (ft_error(2, ERROR_PWD_PARAMS, NULL));
	client->state = STATE_WAITING_FOR_STR;
}

void	send_rm_request(t_cli *client, char **cmds, size_t len)
{
	if (len == 2)
		enqueue_msg(client, cmds[1], ft_strlen(cmds[1]), TYPE_RM);
	else
		return (ft_error(2, ERROR_RM_PARAMS, NULL));
	client->state = STATE_WAITING_FOR_STR;
}
