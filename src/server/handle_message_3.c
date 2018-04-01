/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_message_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 23:05:35 by pribault          #+#    #+#             */
/*   Updated: 2018/04/01 17:50:21 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		check_file_name(char *file)
{
	size_t	i;

	i = (size_t)-1;
	while (++i < FILE_NAME_MAX_SIZE)
		if (!file[i])
			return (1);
	return (0);
}

void	rm_file(t_serv *server, void *client, char *file)
{
	if (remove(file) == -1)
		enqueue_msg(server, client, new_msg(
		"\e[38;5;160mERROR:\e[0m cannot remove file", 40), TYPE_STR);
	else
		enqueue_msg(server, client, new_msg("\e[38;5;82mSUCCESS\e[0m", 21),
		TYPE_STR);
}

void	recv_rm(t_serv *server, void *client, t_header *ptr, size_t size)
{
	char	*file;
	char	*tmp;
	t_data	*data;

	if (!(data = server_client_get_data(client)))
		return (ft_error(2, ERROR_CUSTOM, "client data null, wtf ?!? ._."));
	if (!(tmp = malloc(size - sizeof(t_header) + 1)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	ft_memcpy(tmp, &ptr[1], size - sizeof(t_header));
	tmp[size - sizeof(t_header)] = '\0';
	if (!(file = ft_joinf("%s/%s", data->pwd, tmp)))
		return (ft_error(2, ERROR_ALLOCATION, NULL));
	if (path_is_valid(server, data, ft_reduce_path(file)))
		rm_file(server, client, file);
	else
		enqueue_msg(server, client, new_msg(
		"\e[38;5;160mERROR:\e[0m cannot open file", 38), TYPE_STR);
	free(file);
	free(tmp);
}

#include <errno.h>

void	move_file(t_serv *server, void *client, char *from, char *to)
{
	struct stat	buff;
	void		*ptr;
	int			fd[2];

	ptr = NULL;
	if ((fd[0] = open(from, O_RDONLY)) == -1 || 
		fstat(fd[0], &buff) == -1 ||
		(fd[1] = open(to, O_CREAT | O_WRONLY | O_TRUNC,
			buff.st_mode)) == -1 ||
		!(ptr = mmap(NULL, buff.st_size, PROT_READ, MAP_FILE | MAP_PRIVATE,
			fd[0], 0)) ||
		write(fd[1], ptr, buff.st_size) == -1)
	{
		if (ptr)
			munmap(ptr, buff.st_size);
		close(fd[0]);
		close(fd[1]);
		return (enqueue_msg(server, client, new_msg(
		"\e[38;5;160mERROR:\e[0m cannot open file", 38), TYPE_STR));
	}
	munmap(ptr, buff.st_size);
	close(fd[0]);
	close(fd[1]);
	rm_file(server, client, from);
}

void	recv_mv(t_serv *server, void *client, t_header *ptr, size_t size)
{
	t_data	*data;
	char	move[2][FILE_NAME_MAX_SIZE];
	char	*from;
	char	*to;

	if (!(data = server_client_get_data(client)))
		return (ft_error(2, ERROR_CUSTOM, "client data null, wtf ?!? ._."));
	if (size != sizeof(t_header) + 2 * FILE_NAME_MAX_SIZE)
		return (enqueue_msg(server, client, new_msg(
		"\e[38;5;160mERROR:\e[0m request not well formated", 47), TYPE_STR));
	ft_memcpy(&move, &ptr[1], 2 * FILE_NAME_MAX_SIZE);
	if (!check_file_name(&move[0][0]) || !check_file_name(&move[1][0]))
		return (ft_error(2, ERROR_CUSTOM, "corrupted file name"));
	if (!(from = ft_joinf("%s/%s", data->pwd, &move[0])) ||
		!(to = ft_joinf("%s/%s", data->pwd, &move[1])))
		return (ft_error(2, ERROR_ALLOCATION, NULL));
	if (path_is_valid(server, data, ft_reduce_path(from)) &&
		path_is_valid(server, data, ft_reduce_path(to)))
		move_file(server, client, from, to);
	else
		enqueue_msg(server, client, new_msg(
		"\e[38;5;160mERROR:\e[0m invalid path", 34), TYPE_STR);
	free(from);
	free(to);
}
