/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 11:04:44 by pribault          #+#    #+#             */
/*   Updated: 2018/01/14 21:13:09 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <sys/select.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <signal.h>
# include <errno.h>
# include <netdb.h>
# include "libft.h"
# include "protocol.h"

# define TCP	SOCK_STREAM
# define UDP	SOCK_DGRAM

# define READ_BUFFER_SIZE	1024

# define WHITESPACES		"\a\b\t\n\v\f\r "

typedef struct		s_towrite
{
	int				fd;
	void			*data;
	size_t			size;
}					t_towrite;

typedef struct		s_client
{
	char			*addr;
	char			*service;
	int				socket;
	int				protocol;
	uint16_t		port;
	struct timeval	timeout;
	t_vector		*write_queue;
	fd_set			in;
	fd_set			out;
	int				state;
	void			*data;
}					t_client;

typedef struct		s_waiting
{
	t_header		*data;
	size_t			size;
	size_t			exp;
	uint8_t			state;
}					t_waiting;

typedef void		(*t_function)(t_client*, void*, size_t);

void				error(int error, int state, void *param);

void				get_flags(t_client *client, int argc, char **argv);

void				connect_to_server(t_client *client);

void				run_client(t_client *client);

void				read_from_terminal(t_client *client, int *n);
void				read_from_socket(t_client *client, int *n);

void				write_output(t_client *client, int *n);
void				enqueue_putendl(t_client *client, int fd, char *s,
					size_t len);
void				enqueue_write(t_client *client, int fd, void *data,
					size_t size);

void				treat_message(t_client *client, t_header *msg,
					size_t size);

void				do_nothing(t_client *client, void *msg, size_t size);
void				get_raw_text(t_client *client, void *msg, size_t size);

extern t_client		*g_global;
extern t_function	g_state_machine[STATE_MAX][TYPE_MAX];
extern char			*g_types_name[TYPE_MAX];

#endif
