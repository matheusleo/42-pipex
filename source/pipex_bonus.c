/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:08:10 by mleonard          #+#    #+#             */
/*   Updated: 2022/12/01 02:39:28 by mleonard         ###   ########.fr       */
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

int	here_doc(t_pipex *pipex_data)
{
	int		pid_1;
	int		pid_2;
	char	*line;
	int		counter;

	counter = 0;
	if (pipe(pipex_data->pipes[0]) == ERR)
		error_func("pipe", pipex_data);
	if (pipe(pipex_data->pipes[1]) == ERR)
		error_func("pipe", pipex_data);
	while (TRUE)
	{
		ft_printf("pipex$> ");
		line = get_next_line(STDOUT);
		if (ft_strncmp(line, pipex_data->limiter, ft_strlen(pipex_data->limiter)) == 0)
		{
			free(line);
			break;
		}
		ft_putstr_fd(line, pipex_data->pipes[0][INPUT]);
		free(line);
		counter++;
	}
	pid_1 = create_child(pipex_data);
	if (pid_1 == 0)
	{
		close(pipex_data->pipes[0][INPUT]);
		dup2(pipex_data->pipes[0][OUTPUT], STDIN);
		dup2(pipex_data->pipes[1][INPUT], STDOUT);
		execve(
			parse_program_path(pipex_data->cmds[0], pipex_data),
			parse_program_args(pipex_data->cmds[0]),
			__environ
			);
	}
	close_pipe(pipex_data->pipes[0]);
	waitpid(pid_1, NULL, 0);

	pid_2 = create_child(pipex_data);
	if (pid_2 == 0)
	{
		close(pipex_data->pipes[1][INPUT]);
		dup2(pipex_data->pipes[1][OUTPUT], STDIN);
		dup2(pipex_data->outfile, STDOUT);
		execve(
			parse_program_path(pipex_data->cmds[1], pipex_data),
			parse_program_args(pipex_data->cmds[1]),
			__environ
			);
	}
	close_pipe(pipex_data->pipes[1]);
	waitpid(pid_2, NULL, 0);
	return (OK);
}

int	pipex(t_pipex *pipex_data)
{
	int	pid_idx;

	if (pipex_data->here_doc)
		return (here_doc(pipex_data));
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
