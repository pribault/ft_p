/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_message_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 18:47:16 by pribault          #+#    #+#             */
/*   Updated: 2018/04/01 12:03:14 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	send_file(t_serv *server, void *client, char *file)
{
	t_file_data	*final;
	struct stat	buff;
	char		*s;
	int			fd;

	if ((fd = open(file, O_RDONLY)) == -1 || fstat(fd, &buff) == -1)
		return (enqueue_msg(server, client, new_msg(
		"\e[38;5;160mERROR:\e[0m cannot open file", 38), TYPE_STR));
	if ((buff.st_mode & S_IFMT) != S_IFREG)
		return (enqueue_msg(server, client, new_msg(
		"\e[38;5;160mERROR:\e[0m not a regular file", 40), TYPE_STR));
	if (!(s = mmap(NULL, buff.st_size, PROT_READ, MAP_FILE | MAP_PRIVATE,
		fd, 0)) || !(final = malloc(buff.st_size + sizeof(t_file_data))))
		return (ft_error(2, ERROR_ALLOCATION, NULL));
	enqueue_msg(server, client, new_msg("\e[38;5;82mSUCCESS\e[0m", 21),
	TYPE_STR);
	final->prot = buff.st_mode;
	ft_memcpy((void*)final + sizeof(t_file_data), s, buff.st_size);
	enqueue_msg(server, client, new_msg(final, buff.st_size +
	sizeof(t_file_data)), TYPE_RAW);
	free(final);
	munmap(s, buff.st_size);
}

char	*get_corrected_path(char *path)
{
	char	**array;
	char	*result;
	char	*tmp;

	tmp = NULL;
	result = NULL;
	if (!(array = ft_multisplit(path, "/")) ||
		!(tmp = ft_implode(array, '/')) ||
		!(result = ft_joinf("/%s", tmp)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	ft_free_array((void*)array, ft_arraylen(array));
	free(tmp);
	return (result);
}

void	recv_put(t_serv *server, void *client, t_header *ptr, size_t size)
{
	t_file_data	*file;
	char		*name;
	struct stat	buff;
	int			fd;

	if (size < sizeof(t_header) + sizeof(t_file_data))
		return (ft_error(2, ERROR_CUSTOM,
		"message too small to be of type put"));
		file = (void*)ptr + sizeof(t_header);
	if (!(name = ft_joinf("%s/%s",
		((t_data*)server_client_get_data(client))->pwd, &file->name)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	if (stat(name, &buff) != -1)
		return (enqueue_msg(server, client,
		new_msg("\e[38;5;160mERROR:\e[0m file already exist", 40), TYPE_STR));
		if ((fd = open(name, O_CREAT | O_WRONLY, file->prot)) == -1)
		return (enqueue_msg(server, client,
		new_msg("\e[38;5;160mERROR:\e[0m cannot create file", 40), TYPE_STR));
		write(fd, (void*)file + sizeof(t_file_data),
	size - sizeof(t_header) - sizeof(t_file_data));
	close(fd);
	free(name);
	enqueue_msg(server, client, new_msg("\e[38;5;82mSUCCESS\e[0m", 21),
	TYPE_STR);
}

void	recv_get(t_serv *server, void *client, t_header *ptr, size_t size)
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
	if (path_is_valid(server, data, file))
		send_file(server, client, file);
	else
		enqueue_msg(server, client, new_msg(
		"\e[38;5;160mERROR:\e[0m cannot open file", 38), TYPE_STR);
	free(file);
	free(tmp);
}
