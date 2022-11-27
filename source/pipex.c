/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:08:10 by mleonard          #+#    #+#             */
/*   Updated: 2022/11/27 16:47:38 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	pipex(t_pipex *pipex_data)
{
	int	pipe_fds[2];
	int	pid_1;
	int	pid_2;

	if (pipe(pipe_fds) == ERR)
		error_func("pipe");
	pid_1 = fork();
	if (pid_1 == ERR)
		error_func("fork");
	if (pid_1 == 0)
	{
		close(pipe_fds[OUTPUT]);
		dup2(pipex_data->infile, STDIN);
		dup2(pipe_fds[INPUT], STDOUT);
		execve(pipex_data->cmd_path_1, pipex_data->cmd_1, __environ);
	}
	waitpid(pid_1, NULL, 0);
	pid_2 = fork();
	if (pid_2 == ERR)
		error_func("fork");
	if (pid_2 == 0)
	{
		close(pipe_fds[INPUT]);
		dup2(pipe_fds[OUTPUT], STDIN);
		dup2(pipex_data->outfile, STDOUT);
		execve(pipex_data->cmd_path_2, pipex_data->cmd_2, __environ);
	}
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	waitpid(pid_2, NULL, 0);
	return (OK);
}
