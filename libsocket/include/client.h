/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 22:51:55 by pribault          #+#    #+#             */
/*   Updated: 2018/01/21 14:17:06 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

/*
****************
**	includes  **
****************
*/

# include <sys/socket.h>
# include <netdb.h>
# include "libft.h"

/*
***************
**	defines  **
***************
*/

# define READ_BUFFER_SIZE		65536

/*
**	default client values
*/

# define CLIENT_DEFAULT_QUEUE_MAX	10
# define CLIENT_DEFAULT_TIMEOUT_S	1
# define CLIENT_DEFAULT_TIMEOUT_US	0

/*
**	client opt's masks
*/

# define CLIENT_RUNNING		0x1
# define CLIENT_CONNECTED	0x2

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
	CONNECT_CB,
	DISCONNECT_CB,
	MSG_RECV_CB,
	MSG_SEND_CB,
	EXCEPTION_CB,
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

typedef struct		s_towrite
{
	int				fd;
	t_msg			data;
}					t_towrite;

typedef struct		s_client
{
	t_protocol		protocol;
	int				sockfd;
	struct sockaddr	addr;
	socklen_t		addr_len;
	struct timeval	timeout;
	t_vector		*write_queue;
	uint8_t			opt;
	void			(*connect)(struct s_client*);
	void			(*disconnect)(struct s_client*);
	void			(*msg_recv)(struct s_client*, t_msg*);
	void			(*msg_send)(struct s_client*, int fd, t_msg*);
	void			(*excpt)(struct s_client*);
}					t_client;

/*
*****************
**	functions  **
*****************
*/

t_client			*client_new(void);
int					client_connect(t_client *client, t_protocol protocol,
					char *address, char *port);
void				client_disconnect(t_client *client);
void				client_set_callback(t_client *client, t_callback cb,
					void *ptr);
void				client_poll_events(t_client *client);
void				client_get_incoming_message(t_client *client, int *n_evts);
void				client_manage_write_requests(t_client *client, fd_set *set,
					int *n_evts);
void				client_enqueue_write_by_fd(t_client *client, int fd,
					t_msg *msg);

#endif
