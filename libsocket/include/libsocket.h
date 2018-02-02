/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsocket.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 11:15:22 by pribault          #+#    #+#             */
/*   Updated: 2018/02/02 16:11:08 by pribault         ###   ########.fr       */
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
	SERVER_CLIENT_EXCEPTION_CB,
	SERVER_SERVER_EXCEPTION_CB,
	SERVER_CALLBACK_MAX
}				t_server_callback;

/*
**	structures
*/

typedef struct	s_msg
{
	void		*ptr;
	size_t		size;
}				t_msg;

/*
************************
**	client functions  **
************************
*/

void			*client_new(void);
int				client_connect(void *client, t_protocol protocol,
				char *address, char *port);
void			client_disconnect(void *client);
void			client_set_callback(void *client, t_client_callback cb,
				void *ptr);
void			client_poll_events(void *client);
void			client_get_incoming_message(void *client, int *n_evts);
void			client_manage_write_requests(void *client, fd_set *set,
				int *n_evts);

/*
************************
**	server functions  **
************************
*/

void			*server_new(void);
void			server_delete(void **server);
int				server_start(void *server, t_protocol protocol,
				char *port);
void			server_stop(void *server);
void			server_attach_data(void *server, void *data);
void			*server_get_data(void *server);
void			server_set_callback(void *server, t_server_callback cb,
				void *ptr);
void			server_poll_events(void *server);
void			server_remove_client(void *server, void *client);
int				server_get_client_fd(void *client);
void			server_enqueue_write(void *server, void *client,
				t_msg *msg);
void			server_enqueue_write_by_fd(void *server, int fd,
				t_msg *msg);
void			server_add_client_by_fd(void *server, int fd);
char			*server_get_client_address(void *client);
void			server_client_attach_data(void *client, void *data);
void			*server_client_get_data(void *client);
int				server_set_queue_max(void *server, int max);
int				server_get_queue_max(void *server);
void			server_set_clients_max(void *server, size_t max);
size_t			server_get_clients_max(void *server);
int				server_connect(void *server, t_protocol protocol,
				char *address, char *port);
void			server_set_timeout(void *server,
				struct timeval timeout);
struct timeval	server_get_timeout(void *server);;

#endif
