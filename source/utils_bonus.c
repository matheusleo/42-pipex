/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 16:40:30 by mleonard          #+#    #+#             */
/*   Updated: 2022/12/01 22:20:25 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

int	create_child(t_pipex *pipex_data)
{
	int	pid;

	pid = fork();
	if (pid == ERR)
		error_func("fork", pipex_data);
	return (pid);
}

int	get_fd(char *file_name, int flags, t_pipex *pipex_data)
{
	int	fd;

	fd = open(file_name, O_RDWR | flags);
	if (fd == ERR)
		error_open(file_name, pipex_data);
	return (fd);
}

void	close_pipe(int pipe[2])
{
	if (pipe[OUTPUT] != 1 && pipe[INPUT] != 0)
	{
		close(pipe[0]);
		close(pipe[1]);
	}
}

void	free_vector(char **splitted)
{
	int	idx;

	idx = 0;
	while (splitted[idx])
		free(splitted[idx++]);
	free(splitted);
}
