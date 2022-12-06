/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 16:40:30 by mleonard          #+#    #+#             */
/*   Updated: 2022/12/06 02:58:57 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

char	*remove_all(char *str, int old)
{
	char	**str_splitted;
	char	*new_str;
	char	*temp;
	int		idx;

	str_splitted = ft_split(str, old);
	new_str = ft_strdup(str_splitted[0]);
	idx = 1;
	while(str_splitted[idx])
	{
		temp = ft_strjoin(new_str, str_splitted[idx]);
		free(new_str);
		new_str = ft_strdup(temp);
		free(temp);
		idx++;
	}
	free_vector(str_splitted);
	return (new_str);
}

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

	fd = open(file_name, O_RDWR | flags, 0644);
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
