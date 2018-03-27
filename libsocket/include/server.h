/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 22:51:48 by pribault          #+#    #+#             */
/*   Updated: 2018/01/21 13:46:21 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

/*
****************
**	includes  **
****************
*/

# include <sys/socket.h>
# include <arpa/inet.h>
# include <netdb.h>
# include "libft.h"

/*
***************
**	defines  **
***************
*/

# define READ_BUFFER_SIZE		65536
# define CIRCULAR_BUFFER_SIZE	128

/*
**	default server values
*/

# define SERVER_DEFAULT_QUEUE_MAX	2
# define SERVER_DEFAULT_TIMEOUT_S	1
# define SERVER_DEFAULT_TIMEOUT_US	0

/*
**	server opt's masks
*/

# define SERVER_RUNNING		0x1

/*
*************
**	enums  **
*************
*/

typedef enum		e_protocol
{
	TCP = SOCK_STREAM,
	UDP = SOCK_DGRAM
}					t_protocol;

typedef enum		e_callback
{
	CLIENT_ADD_CB,
	CLIENT_DEL_CB,
	MSG_RECV_CB,
	MSG_SEND_CB,
	CLIENT_EXCEPTION_CB,
	SERVER_EXCEPTION_CB,
	CALLBACK_MAX
}					t_callback;

/*
******************
**	structures  **
******************
*/

typedef struct		s_msg
{
	void			*ptr;
	size_t			size;
}					t_msg;

typedef struct		s_client
{
	int				fd;
	struct sockaddr	addr;
	socklen_t		addr_len;
	struct timeval	last;
	void			*data;
}					t_client;

typedef struct		s_towrite
{
	t_client		client;
	t_msg			data;
}					t_towrite;

typedef struct		s_server
{
	t_protocol		protocol;
	int				sockfd;
	int				queue_max;
	struct timeval	timeout;
	t_vector		clients;
	t_circ_buffer	write_queue;
	uint16_t		port;
	uint8_t			opt;
	void			*data;
	void			(*client_add)(struct s_server*, t_client*);
	void			(*client_del)(struct s_server*, t_client*);
	void			(*msg_recv)(struct s_server*, t_client*, t_msg*);
	void			(*msg_send)(struct s_server*, t_client*, t_msg*);
	void			(*client_excpt)(struct s_server*, t_client*);
	void			(*server_excpt)(struct s_server*);
}					t_server;

/*
*****************
**	functions  **
*****************
*/

/*
**	public functions
*/

t_server			*server_new(t_protocol protocol);
void				server_delete(t_server **server);
int					server_start(t_server *server, char *port);
void				server_stop(t_server *server);
void				server_attach_data(t_server *server, void *data);
void				*server_get_data(t_server *server);
void				server_set_callback(t_server *server, t_callback cb,
					void *ptr);
void				server_poll_events(t_server *server);
void				server_remove_client(t_server *server, t_client *client);
int					server_get_client_fd(t_client *client);
void				server_enqueue_write(t_server *server, t_client *client,
					t_msg *msg);
void				server_enqueue_write_by_fd(t_server *server, int fd,
					t_msg *msg);
void				server_add_client_by_fd(t_server *server, int fd);
char				*server_get_client_address(t_client *client);
void				server_client_attach_data(t_client *client, void *data);
void				*server_client_get_data(t_client *client);
int					server_set_queue_max(t_server *server, int max);
int					server_get_queue_max(t_server *server);
int					server_connect(t_server *server, char *address,
					char *port);

/*
**	private functions, used for internal management
*/

void				server_add_incoming_client(t_server *server, int *n_evts);
void				server_manage_incoming_messages(t_server *server,
					fd_set *set, fd_set *err_set, int *n_evts);
void				server_manage_write_requests(t_server *server,
					fd_set *set, int *n_evts);

#endif
