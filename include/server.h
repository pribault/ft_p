/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 11:04:44 by pribault          #+#    #+#             */
/*   Updated: 2018/03/28 13:29:23 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "protocol.h"
# include <errno.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/mman.h>

# define OPT_VERBOSE	BYTE(0)

typedef enum	e_server_error
{
	ERROR_NOT_IN_PORT_RANGE = ERROR_FT_MAX,
	ERROR_PORT_ALREADY_SET,
	ERROR_NO_PORT_SET,
	ERROR_INVALID_PROTOCOL,
	ERROR_MSG_TOO_SMALL,
	ERROR_UNEXPECTED_MSG,
	ERROR_UNKNOWN_MSG_TYPE,
	ERROR_FILE_ALREADY_EXIST,
	ERROR_INVALID_ROOT
}				t_server_error;

typedef struct	s_data
{
	int			state;
	char		*pwd;
	void		*ptr;
	uint32_t	size;
	uint32_t	expected;
	t_file_data	*file;
}				t_data;

typedef struct	s_serv
{
	t_server	*server;
	char		**env;
	char		*port;
	char		*root;
	t_protocol	protocol;
	uint8_t		opt;
}				t_serv;

typedef void	(*t_msg_handler)(t_serv *, void *, t_header *, size_t);

void			print_usage(void);
void			get_default(char *s, t_serv *server);
void			set_verbose(t_serv *server);
void			set_long_verbose(t_serv *server, char **args,
				int n_params);
void			get_root(t_serv *server, char **args, int n_params);
void			get_port(t_serv *server, char **args, int n);
void			get_protocol(t_serv *server, char **args, int n_params);
void			get_max(t_serv *server, char **args, int n_params);
void			get_timeout(t_serv *server, char **args, int n_params);

void			add_client(void *server, void *client);
void			del_client(void *server, void *client);
void			msg_recv(void *server, void *client, t_msg *msg);
void			msg_send(void *server, void *client, t_msg *msg);
void			trash_msg(void *server, void *client, t_msg *msg);

void			treat_command(t_serv *server, char *cmd);

void			manage_received_msg(t_serv *server, void *client,
				t_header *ptr, size_t size);

int				path_is_valid(t_serv *server, t_data *data, char *file);
void			recv_cd(t_serv *server, void *client, t_header *ptr,
				size_t size);
void			recv_ls(t_serv *server, void *client, t_header *ptr,
				size_t size);
void			recv_pwd(t_serv *server, void *client, t_header *ptr,
				size_t size);
void			recv_put(t_serv *server, void *client, t_header *ptr,
				size_t size);
void			recv_get(t_serv *server, void *client, t_header *ptr,
				size_t size);

t_msg			new_msg(void *ptr, size_t size);
void			enqueue_msg(t_serv *server, void *client, t_msg msg,
				uint8_t type);

#endif
