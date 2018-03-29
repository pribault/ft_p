/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsocket.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 11:15:22 by pribault          #+#    #+#             */
/*   Updated: 2018/03/29 18:03:46 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSOCKET_H
# define LIBSOCKET_H

/*
****************
**	includes  **
****************
*/

# include <sys/socket.h>
# include <inttypes.h>
# include <unistd.h>

/*
*************
**	types  **
*************
*/

/*
**	enums
*/

typedef enum	e_protocol
{
	TCP = SOCK_STREAM,
	UDP = SOCK_DGRAM
}				t_protocol;

typedef enum	e_domain
{
	IPV4 = AF_INET,
	IPV6 = AF_INET6
}				t_domain;

typedef enum	e_client_callback
{
	CLIENT_CONNECT_CB,
	CLIENT_DISCONNECT_CB,
	CLIENT_MSG_RECV_CB,
	CLIENT_MSG_SEND_CB,
	CLIENT_EXCEPTION_CB,
	CLIENT_CALLBACK_MAX
}				t_client_callback;

typedef enum	e_server_callback
{
	SERVER_CLIENT_ADD_CB,
	SERVER_CLIENT_DEL_CB,
	SERVER_MSG_RECV_CB,
	SERVER_MSG_SEND_CB,
	SERVER_MSG_TRASH_CB,
	SERVER_CLIENT_EXCEPTION_CB,
	SERVER_SERVER_EXCEPTION_CB,
	SERVER_CALLBACK_MAX
}				t_server_callback;

/*
**	structures
*/

typedef struct	s_method
{
	t_protocol	protocol;
	t_domain	domain;
}				t_method;

typedef struct	s_msg
{
	void		*ptr;
	size_t		size;
}				t_msg;

/*
**	others
*/

/*
**	warning, t_client is different
**	between client and server functions
*/

typedef void	*t_client;
typedef void	*t_server;

/*
************************
**	client functions  **
************************
*/

t_client		*client_new(void);
int				client_connect(t_client *client, t_protocol protocol,
				char *address, char *port);
void			client_disconnect(t_client *client);
void			client_set_callback(t_client *client, t_client_callback cb,
				void *ptr);
void			client_poll_events(t_client *client);
void			client_get_incoming_message(t_client *client, int *n_evts);
void			client_manage_write_requests(t_client *client, fd_set *set,
				int *n_evts);

/*
************************
**	server functions  **
************************
*/

t_server		*server_new(void);
void			server_delete(t_server **server);
int				server_start(t_server *server, t_method method, char *port);
void			server_stop(t_server *server);
void			server_attach_data(t_server *server, void *data);
void			*server_get_data(t_server *server);
void			server_set_callback(t_server *server, t_server_callback cb,
				void *ptr);
void			server_poll_events(t_server *server);
void			server_remove_client(t_server *server, t_client *client);
int				server_get_client_fd(t_client *client);
void			server_enqueue_write(t_server *server, t_client *client,
				t_msg *msg);
void			server_enqueue_write_by_fd(t_server *server, int fd,
				t_msg *msg);
void			server_enqueue_write_by_address(t_server *server,
				void *address, t_msg *msg);
void			server_add_client_by_fd(t_server *server, int fd);
void			*server_get_client_address(t_client *client);
void			server_client_attach_data(t_client *client, void *data);
void			*server_client_get_data(t_client *client);
int				server_set_queue_max(t_server *server, int max);
int				server_get_queue_max(t_server *server);
int				server_connect(t_server *server, t_method method,
				char *address, char *port);
void			client_enqueue_write_by_fd(t_client *client, int fd,
				t_msg *msg);
void			server_set_timeout(t_server *server, uint64_t seconds,
				uint64_t micro_seconds);
struct timeval	*server_get_timeout(t_server *server);

#endif
