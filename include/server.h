/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 11:04:44 by pribault          #+#    #+#             */
/*   Updated: 2018/01/21 19:35:01 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "libsocket.h"
# include "libft.h"
# include <errno.h>

typedef struct	s_data
{
	char		*pwd;
	void		*data;
	size_t		size;
	size_t		expected;
}				t_data;

typedef struct	s_server
{
	void		*server;
	char		**env;
	char		*port;
	char		*root;
}				t_server;

void			error(int error, int state, void *param);
void			get_flags(t_server *server, int argc, char **argv);
void			print_usage(void);

void			add_client(void *server, void *client);
void			del_client(void *server, void *client);
void			msg_recv(void *server, void *client, t_msg *msg);
void			msg_send(void *server, void *client, t_msg *msg);

void			treat_command(t_server *server, char *cmd);

#endif
