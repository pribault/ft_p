/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 11:04:44 by pribault          #+#    #+#             */
/*   Updated: 2018/01/21 20:15:36 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include "libsocket.h"
# include "libft.h"
# include <errno.h>

typedef struct	s_client
{
	void		*server;
	char		*address;
	char		*port;
	char		**env;
	int			fd;
}				t_client;

void			error(int error, int state, void *param);
void			get_flags(t_client *client, int argc, char **argv);
void			print_usage(void);

void			add_client(void *server, void *client);
void			del_client(void *server, void *client);

void			msg_recv(void *server, void *client, t_msg *msg);
void			msg_send(void *server, void *client, t_msg *msg);

void			treat_command(t_client *client, char *cmd);

#endif
