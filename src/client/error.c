#include "client.h"

void	error(int error, int state, void *param)
{
	char	*s;

	ft_putstr_fd("\e[38;5;124m\e[4mError:\e[0m ", 2);
	if (error == -1)
		s = ft_strdup(param);
	else if (error == 0)
		s = strerror(errno);
	else if (error == 10)
		s = ft_joinf("address and port already set, ignoring '%s'", param);
	else if (error == 11)
		s = ft_joinf("'%s' must be a number in interval [0;65536]", param);
	else if (error == 12)
		s = ft_joinf("unknown parameter '%s'", param);
	else if (error == 100)
		s = ft_joinf("cannot connect to '%s'", param);
	else
		s = ft_strdup("unknown error");
	ft_putendl_fd(s, 2);
	free(s);
	if (state)
		exit(state);
}
