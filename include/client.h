#ifndef CLIENT_H
# define CLIENT_H

# include <sys/select.h>
# include <sys/socket.h>
# include <errno.h>
# include <netdb.h>
# include "libft.h"

# define TCP	SOCK_STREAM
# define UDP	SOCK_DGRAM

typedef struct	s_client
{
	char		*addr;
	char		*service;
	int			socket;
	int			protocol;
	uint16_t	port;
}				t_client;

void			error(int error, int state, void *param);

void			get_flags(t_client *client, int argc, char **argv);

void			connect_to_server(t_client *client);

#endif
