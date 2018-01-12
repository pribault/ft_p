#include "server.h"

int		is_input_waiting(int fd, struct timeval timeout)
{
	fd_set	set;
	int		r;

	FD_ZERO(&set);
	FD_SET(fd, &set);
	r = select(fd + 1, &set, NULL, NULL, &timeout);
	if (r < 0)
	{
		error(0, 0, NULL);
		return (0);
	}
	return ((r) ? 1 : 0);
}
