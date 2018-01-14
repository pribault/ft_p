/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 11:04:44 by pribault          #+#    #+#             */
/*   Updated: 2018/01/14 17:19:10 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <sys/select.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <ifaddrs.h>
# include <signal.h>
# include <errno.h>
# include <netdb.h>
# include "libft.h"
# include "protocol.h"

# define TCP	SOCK_STREAM
# define UDP	SOCK_DGRAM

# define VERBOSE	0x1

# define READ_BUFFER_SIZE	1024

typedef struct		s_towrite
{
	int				fd;
	void			*data;
	size_t			size;
}					t_towrite;

typedef struct		s_client
{
	struct sockaddr	addr;
	socklen_t		addr_len;
	struct timeval	last;
	int				fd;
	int				state;
	void			*data;
}					t_client;

typedef struct		s_server
{
	int				socket;
	int				protocol;
	int				queue_max;
	struct timeval	timeout;
	t_vector		*clients;
	t_vector		*write_queue;
	uint16_t		port;
	uint8_t			opt;
	fd_set			in;
	fd_set			out;
	int				io_max;
}					t_server;

typedef struct		s_waiting
{
	void			*data;
	size_t			size;
	t_header		header;
}					t_waiting;

typedef struct		s_writing
{
	int				fd;
	size_t			size;
	size_t			expected;
}					t_writing;

typedef void		(*t_function)(t_server*, t_client*, void*, size_t);

void				print_usage(void);
void				error(int error, int state, void *param);

void				get_flags(t_server *server, int argc, char **argv);
void				get_protocol(t_server *server, int argc, char **argv,
					int *i);

void				start_server(t_server *server);
void				run_server(t_server *server);

void				set_input(t_server *server);
void				read_from_terminal(t_server *server, int *n);
void				read_from_socket(t_server *server, int *n);
void				read_input(t_server *server, int *n);

void				set_output(t_server *server);
void				write_output(t_server *server, int *n);

void				enqueue_putendl(t_server *server, int fd, char *s,
					size_t len);
void				enqueue_write(t_server *server,
					int fd, void *data, size_t size);

void				treat_message(t_server *server, t_client *client,
					t_header *msg, size_t size);

void				get_raw_text(t_server *server, t_client *client, void *msg,
					size_t size);

extern t_server		*g_global;
extern t_function	g_state_machine[STATE_MAX][TYPE_MAX];
extern char			*g_types_name[TYPE_MAX];

#endif
