/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:08:10 by mleonard          #+#    #+#             */
/*   Updated: 2022/12/05 01:49:32 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

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

	if (pipex_data->here_doc)
		return (here_doc(pipex_data));
	pid_idx = 0;
	while (pid_idx < pipex_data->cmds_len)
	{
		if (pipe(pipex_data->pipes[pid_idx % 2]) == ERR)
			error_func("pipe", pipex_data);
		pipex_data->pids[pid_idx] = create_child(pipex_data);
		if (pipex_data->pids[pid_idx] == 0)
		{
			redirect_input_output(pipex_data, pid_idx);
			execve(
				parse_program_path(pipex_data->cmds[pid_idx]),
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
