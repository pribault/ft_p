/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 11:04:44 by pribault          #+#    #+#             */
/*   Updated: 2018/01/13 20:57:36 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <sys/select.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <errno.h>
# include <netdb.h>
# include "libft.h"

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

void				print_usage(void);
void				error(int error, int state, void *param);

void				get_flags(t_server *server, int argc, char **argv);

void				start_server(t_server *server);
void				run_server(t_server *server);

void				set_input(t_server *server);
void				read_input(t_server *server, int *n);

void				set_output(t_server *server);
void				write_output(t_server *server, int *n);

void				enqueue_write(t_server *server,
					int fd, void *data, size_t size);

extern t_server	*g_global;

#endif
