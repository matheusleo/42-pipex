/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:08:10 by mleonard          #+#    #+#             */
/*   Updated: 2022/11/29 23:03:34 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

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

int	pipex(t_pipex *pipex_data)
{
	int	pid_idx;

	pid_idx = 0;
	pipe(pipex_data->pipes[0]);
	pipex_data->pids[pid_idx] = fork();
	if (pipex_data->pids[pid_idx] == 0)
	{
		ft_printf("from child process stored in pid_1\n");
		close(pipex_data->pipes[0][OUTPUT]);
		dup2(pipex_data->infile, STDIN);
		dup2(pipex_data->pipes[0][INPUT], STDOUT);
		execve(
			parse_program_path(pipex_data->cmds[0], pipex_data),
			parse_program_args(pipex_data->cmds[0]),
			__environ
		);
	}
	close_pipe(pipex_data->pipes[1]);
	waitpid(pipex_data->pids[pid_idx], NULL, 0);
	pid_idx++;

	pipe(pipex_data->pipes[1]);
	pipex_data->pids[pid_idx] = fork();
	if (pipex_data->pids[pid_idx] == 0)
	{
		ft_printf("from child process stored in pid_2\n");
		close(pipex_data->pipes[0][INPUT]);
		dup2(pipex_data->pipes[0][OUTPUT], STDIN);
		dup2(pipex_data->pipes[1][INPUT], STDOUT);
		execve(
			parse_program_path(pipex_data->cmds[1], pipex_data),
			parse_program_args(pipex_data->cmds[1]),
			__environ
		);
	}
	close_pipe(pipex_data->pipes[0]);
	waitpid(pipex_data->pids[pid_idx], NULL, 0);
	pid_idx++;

	pipe(pipex_data->pipes[0]);
	pipex_data->pids[pid_idx] = fork();
	if (pipex_data->pids[pid_idx] == 0)
	{
		ft_printf("from child process stored in pid_3\n");
		close(pipex_data->pipes[1][INPUT]);
		dup2(pipex_data->pipes[1][OUTPUT], STDIN);
		dup2(pipex_data->pipes[0][INPUT], STDOUT);
		execve(
			parse_program_path(pipex_data->cmds[2], pipex_data),
			parse_program_args(pipex_data->cmds[2]),
			__environ
		);
	}
	close_pipe(pipex_data->pipes[1]);
	waitpid(pipex_data->pids[pid_idx], NULL, 0);
	pid_idx++;

	pipex_data->pids[pid_idx] = fork();
	if (pipex_data->pids[pid_idx] == 0)
	{
		ft_printf("from child process stored in pid_4\n");
		close(pipex_data->pipes[0][INPUT]);
		dup2(pipex_data->pipes[0][OUTPUT], STDIN);
		dup2(pipex_data->outfile, STDOUT);
		execve(
			parse_program_path(pipex_data->cmds[3], pipex_data),
			parse_program_args(pipex_data->cmds[3]),
			__environ
		);
	}
	close_pipe(pipex_data->pipes[0]);
	waitpid(pipex_data->pids[pid_idx], NULL, 0);
	pid_idx++;
}
