/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 16:43:12 by pribault          #+#    #+#             */
/*   Updated: 2018/02/03 17:51:32 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	send_put_request_2(t_cli *client, char *file, void *data,
		struct stat *buff)
{
	t_file_data	*final;
	char		*name;

	if (!(final = malloc(buff->st_size + sizeof(t_file_data))))
		ft_error(2, ERROR_ALLOCATION, NULL);
	name = ft_get_file_name_from_path(file);
	ft_memcpy(&final->name, name, ft_strlen(name) + 1);
	final->prot = buff->st_mode;
	ft_memcpy((void*)final + sizeof(t_file_data), data, buff->st_size);
	enqueue_msg(client, final, buff->st_size + sizeof(t_file_data),
	TYPE_PUT);
	free(final);
}

void	send_put_request(t_cli *client, char **cmds, size_t len)
{
	struct stat	buff;
	char		*s;
	int			fd;

	if (len == 2)
	{
		if (ft_strlen(cmds[1]) >= FILE_NAME_MAX_SIZE)
			return (ft_error(2, ERROR_FILE_NAME_TOO_LONG, cmds[1]));
		if ((fd = open(cmds[1], O_RDWR)) == -1 ||
			fstat(fd, &buff) == -1)
			return (ft_error(2, ERROR_FILE, cmds[1]));
		if (!(s = mmap(NULL, buff.st_size, PROT_READ,
			MAP_FILE | MAP_PRIVATE, fd, 0)))
			return (ft_error(2, ERROR_ALLOCATION, NULL));
		send_put_request_2(client, cmds[1], s, &buff);
		munmap(s, buff.st_size);
		close(fd);
	}
	else
		ft_error(2, ERROR_PUT_PARAMS, NULL);
	client->state = STATE_WAITING_FOR_STR;
}

void	send_get_request(t_cli *client, char **cmds, size_t len)
{
	char	*file;
	size_t	name_len;

	if (len == 2)
		enqueue_msg(client, cmds[1], ft_strlen(cmds[1]), TYPE_GET);
	else
		return (ft_error(2, ERROR_GET_PARAMS, NULL));
	file = ft_get_file_name_from_path(cmds[1]);
	name_len = ft_strlen(file);
	if (name_len >= FILE_NAME_MAX_SIZE)
		return (ft_error(2, ERROR_FILE_NAME_TOO_LONG, cmds[1]));
	if (!(client->file = malloc(sizeof(t_file_data))))
		ft_error(2, ERROR_ALLOCATION, NULL);
	ft_memcpy(&client->file->name, file, name_len);
	client->file->name[name_len] = '\0';
	client->file->prot = 0;
	client->state = STATE_WAITING_FOR_STR;
}

void	get_command(t_cli *client, char **cmds, size_t len)
{
	if (!ft_strcmp(cmds[0], "ls"))
		send_ls_request(client, cmds, len);
	else if (!ft_strcmp(cmds[0], "cd"))
		send_cd_request(client, cmds, len);
	else if (!ft_strcmp(cmds[0], "pwd"))
		send_pwd_request(client, cmds, len);
	else if (!ft_strcmp(cmds[0], "quit"))
		quit(client, cmds, len);
	else if (!ft_strcmp(cmds[0], "put"))
		send_put_request(client, cmds, len);
	else if (!ft_strcmp(cmds[0], "get"))
		send_get_request(client, cmds, len);
	else
		ft_error(2, ERROR_UNKNOWN_COMMAND, cmds[0]);
}

void	treat_command(t_cli *client, char *cmd)
{
	char	**cmds;
	size_t	len;

	(void)client;
	if (!(cmds = ft_multisplit(cmd, WHITESPACES)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	len = ft_arraylen(cmds);
	if (len)
		get_command(client, cmds, len);
	ft_free_array((void**)cmds, len);
}
