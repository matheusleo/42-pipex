/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:08:10 by mleonard          #+#    #+#             */
/*   Updated: 2022/11/27 18:52:35 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static int	create_child(t_pipex *pipex_data)
{
	int	pid;

	pid = fork();
	if (pid == ERR)
		error_func("fork", pipex_data);
	return (pid);
}

static void	close_pipe(int pipe[2])
{
	close(pipe[0]);
	close(pipe[1]);
}

static void	exec_write_process(t_pipex *pipex_data)
{
	close(pipex_data->pipe[OUTPUT]);
	dup2(pipex_data->infile, STDIN);
	dup2(pipex_data->pipe[INPUT], STDOUT);
	execve(pipex_data->cmd_path_1, pipex_data->cmd_1, __environ);
}

static void	exec_read_process(t_pipex *pipex_data)
{
	close(pipex_data->pipe[INPUT]);
	dup2(pipex_data->pipe[OUTPUT], STDIN);
	dup2(pipex_data->outfile, STDOUT);
	execve(pipex_data->cmd_path_2, pipex_data->cmd_2, __environ);
}

int	pipex(t_pipex *pipex_data)
{
	int	pid_1;
	int	pid_2;

	if (pipe(pipex_data->pipe) == ERR)
		error_func("pipe", pipex_data);
	pid_1 = create_child(pipex_data);
	if (pid_1 == 0)
		exec_write_process(pipex_data);
	waitpid(pid_1, NULL, 0);
	pid_2 = create_child(pipex_data);
	if (pid_2 == 0)
		exec_read_process(pipex_data);
	close_pipe(pipex_data->pipe);
	waitpid(pid_2, NULL, 0);
	return (OK);
}
