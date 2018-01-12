#ifndef SERVER_H
# define SERVER_H

# include <sys/select.h>
# include <sys/socket.h>
# include <errno.h>
# include <netdb.h>
# include "libft.h"

# define TCP	SOCK_STREAM
# define UDP	SOCK_DGRAM

# define VERBOSE	0x1

typedef struct		s_client
{
	struct sockaddr	addr;
	socklen_t		addr_len;
	fd_set			set;
}					t_client;

typedef struct		s_server
{
	int				socket;
	int				protocol;
	int				queue_max;
	struct timeval	timeout;
	t_vector		*clients;
	uint16_t		port;
	uint8_t			opt;
}					t_server;

void				print_usage(void);
void				error(int error, int state, void *param);

void				get_flags(t_server *server, int argc, char **argv);

void				start_server(t_server *server);
void				run_server(t_server *server);

int					is_input_waiting(int fd, struct timeval timeout);

#endif
