/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 11:04:44 by pribault          #+#    #+#             */
/*   Updated: 2018/02/02 16:30:38 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "libsocket.h"
# include "libft.h"
# include <errno.h>
# include <signal.h>

# define OPT_VERBOSE	BYTE(0)

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
	t_protocol	protocol;
	uint8_t		opt;
}				t_server;

typedef enum	e_server_error
{
	ERROR_NOT_IN_PORT_RANGE = ERROR_FT_MAX,
	ERROR_PORT_ALREADY_SET,
	ERROR_NO_PORT_SET,
	ERROR_INVALID_PROTOCOL
}				t_server_error;

void			print_usage(void);
void			set_verbose(t_server *server);
void			get_default(char *s, t_server *server);
void			get_port(char **args, int n, t_server *server);
void			get_protocol(char **args, int n_params, t_server *server);
void			get_max(char **args, int n_params, t_server *server);
void			get_timeout(char **args, int n_params, t_server *server);

void			add_client(void *server, void *client);
void			del_client(void *server, void *client);
void			msg_recv(void *server, void *client, t_msg *msg);
void			msg_send(void *server, void *client, t_msg *msg);

void			treat_command(t_server *server, char *cmd);

#endif
