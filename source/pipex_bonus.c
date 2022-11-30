/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:08:10 by mleonard          #+#    #+#             */
/*   Updated: 2022/11/30 00:00:15 by mleonard         ###   ########.fr       */
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
	if (pipe[OUTPUT] != 1 && pipe[INPUT] != 0)
	{
		close(pipe[0]);
		close(pipe[1]);
	}
}

static void	redirect_input_output(t_pipex *pipex_data, int cur_pid)
{
	if (cur_pid == 0)
	{
		close(pipex_data->pipes[cur_pid % 2][OUTPUT]);
		dup2(pipex_data->infile, STDIN);
		dup2(pipex_data->pipes[cur_pid % 2][INPUT], STDOUT);
	}
	else
	{
		close(pipex_data->pipes[(cur_pid + 1) % 2][INPUT]);
		dup2(pipex_data->pipes[(cur_pid + 1) % 2][OUTPUT], STDIN);
		if (cur_pid == pipex_data->cmds_len - 1)
			dup2(pipex_data->outfile, STDOUT);
		else
			dup2(pipex_data->pipes[cur_pid % 2][INPUT], STDOUT);
	}
}

int	pipex(t_pipex *pipex_data)
{
	int	pid_idx;

	pid_idx = 0;
	while (pid_idx < pipex_data->cmds_len)
	{
		pipe(pipex_data->pipes[pid_idx % 2]);
		pipex_data->pids[pid_idx] = create_child(pipex_data);
		if (pipex_data->pids[pid_idx] == 0)
		{
			redirect_input_output(pipex_data, pid_idx);
			execve(
				parse_program_path(pipex_data->cmds[pid_idx], pipex_data),
				parse_program_args(pipex_data->cmds[pid_idx]),
				__environ
				);
		}
		close_pipe(pipex_data->pipes[(pid_idx + 1) % 2]);
		waitpid(pipex_data->pids[pid_idx], NULL, 0);
		pid_idx++;
	}
	return (OK);
}
