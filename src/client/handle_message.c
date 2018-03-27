/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_message.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 21:50:14 by pribault          #+#    #+#             */
/*   Updated: 2018/02/03 18:20:25 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	recv_state(t_cli *client, t_header *ptr, size_t size)
{
	(void)size;
	if (ptr->size >= sizeof(t_header) + 5 && !ft_strncmp((void*)ptr +
		sizeof(t_header), "ERROR", 5))
		client->state = STATE_NONE;
}

void	recv_str(t_cli *client, t_header *ptr, size_t size)
{
	static t_msg	msg;
	uint64_t		x;

	if (ptr->type >= TYPE_MAX)
		return (ft_error(2, ERROR_UNKNOWN_MSG_TYPE, (void*)(x = ptr->type)));
	if (ptr->type != TYPE_STR)
		return (ft_error(2, ERROR_EXPECTING_STR, (void*)(x = ptr->type)));
	if (!(msg.ptr = malloc(size - sizeof(t_header) + 1)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	ft_memcpy(msg.ptr, (void*)ptr + sizeof(t_header), size - sizeof(t_header));
	((char*)msg.ptr)[size - sizeof(t_header)] = '\n';
	msg.size = size - sizeof(t_header) + 1;
	server_enqueue_write_by_fd(client->server, 1, &msg);
	if (!ft_strncmp(msg.ptr, "ERROR: ", 7))
	{
		if (client->file)
			ft_memdel((void**)&client->file);
		client->state = STATE_NONE;
	}
	else if (client->file)
		client->state = STATE_WAITING_FOR_FILE;
}

void	recv_file(t_cli *client, t_header *ptr, size_t size)
{
	struct stat	buff;
	int			fd;

	if (stat((char*)&client->file->name, &buff) != -1)
		ft_error(2, ERROR_FILE_ALREADY_EXIST, &client->file->name);
	else
	{
		if ((fd = open((char*)&client->file->name, O_CREAT | O_WRONLY,
			((t_file_data*)((void*)ptr + sizeof(t_header)))->prot)) == -1)
			return (ft_error(2, ERROR_FILE, &client->file->name));
		write(fd, (void*)ptr + sizeof(t_header) + sizeof(t_file_data),
		size - sizeof(t_header) - sizeof(t_file_data));
		close(fd);
	}
	ft_memdel((void**)&client->file);
	client->state = STATE_NONE;
}
