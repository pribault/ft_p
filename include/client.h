/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 11:04:44 by pribault          #+#    #+#             */
/*   Updated: 2018/02/03 17:27:55 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include "protocol.h"
# include <errno.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/mman.h>

# define OPT_VERBOSE	BYTE(0)

typedef enum	e_client_error
{
	ERROR_NOT_IN_PORT_RANGE = ERROR_FT_MAX,
	ERROR_ADDRESS_ALREADY_SET,
	ERROR_PORT_ALREADY_SET,
	ERROR_PARAMS_ALREADY_SET,
	ERROR_NO_ADDRESS_SET,
	ERROR_NO_PORT_SET,
	ERROR_INVALID_PROTOCOL,
	ERROR_CANNOT_CONNECT,
	ERROR_MSG_TOO_SMALL,
	ERROR_UNEXPECTED_MSG,
	ERROR_UNKNOWN_MSG_TYPE,
	ERROR_EXPECTING_STR,
	ERROR_LS_PARAMS,
	ERROR_CD_PARAMS,
	ERROR_PWD_PARAMS,
	ERROR_PUT_PARAMS,
	ERROR_GET_PARAMS,
	ERROR_EXIT_PARAMS,
	ERROR_UNKNOWN_COMMAND,
	ERROR_FILE_ALREADY_EXIST,
	ERROR_FILE_NAME_TOO_LONG
}				t_client_error;

typedef struct	s_data
{
	void		*ptr;
	uint32_t	size;
	uint32_t	expected;
}				t_data;

typedef struct	s_client
{
	void		*server;
	char		*address;
	char		*port;
	char		**env;
	t_protocol	protocol;
	int			fd;
	uint8_t		opt;
	t_data		data;
	int			state;
	t_file_data	*file;
}				t_client;

typedef struct	s_state_func
{
	t_state		state;
	void		(*function)(t_client *client, t_header *ptr, size_t size);
}				t_state_func;

typedef void	(*t_msg_handler)(t_client *, t_header *, size_t);

void			print_usage(void);
void			set_verbose(t_client *client);
void			set_long_verbose(char **args, int n_params,
				t_client *client);
void			get_default(char *s, t_client *client);
void			get_port(char **args, int n_params, t_client *client);
void			get_address(char **args, int n_params, t_client *client);
void			get_protocol(char **args, int n_params, t_client *client);
void			get_timeout(char **args, int n_params, t_client *client);

void			add_client(void *server, void *client);
void			del_client(void *server, void *client);

void			msg_recv(void *server, void *client, t_msg *msg);
void			msg_send(void *server, void *client, t_msg *msg);

void			enqueue_msg(t_client *client, void *data, size_t size,
				uint8_t type);

void			manage_received_msg(t_client *client, t_header *ptr,
				size_t size);

void			quit(t_client *client, char **cmds, size_t len);
void			send_ls_request(t_client *client, char **cmds, size_t len);
void			send_cd_request(t_client *client, char **cmds, size_t len);
void			send_pwd_request(t_client *client, char **cmds, size_t len);

void			recv_state(t_client *client, t_header *ptr, size_t size);
void			recv_str(t_client *client, t_header *ptr, size_t size);
void			recv_file(t_client *client, t_header *ptr, size_t size);

void			treat_command(t_client *client, char *cmd);

#endif
