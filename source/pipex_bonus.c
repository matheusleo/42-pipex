/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:08:10 by mleonard          #+#    #+#             */
/*   Updated: 2022/11/29 00:36:08 by mleonard         ###   ########.fr       */
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
	int	pid_1;
	int	pid_2;
	int	pid_3;
	int	pid_4;
	int	pipe_1[2];
	int	pipe_2[2];
	int	pipe_3[2];

	pipe(pipe_1);
	pipe(pipe_2);
	pipe(pipe_3);
	pid_1 = fork();
	if (pid_1 == 0)
	{
		// Child process for first cmd
		ft_printf("from the first child process\n");
		close(pipe_1[OUTPUT]);
		dup2(pipex_data->infile, STDIN);
		dup2(pipe_1[INPUT], STDOUT);
		execve(
			parse_program_path(pipex_data->cmds[0], pipex_data),
			parse_program_args(pipex_data->cmds[0]),
			__environ
		);
	}
	pid_2 = fork();
	if (pid_2 == 0)
	{
		// Child process for second cmd
		ft_printf("from the second child process\n");
		close(pipe_1[INPUT]);
		dup2(pipe_1[OUTPUT], STDIN);
		dup2(pipe_2[INPUT], STDOUT);
		execve(
			parse_program_path(pipex_data->cmds[1], pipex_data),
			parse_program_args(pipex_data->cmds[1]),
			__environ
		);
	}
	pid_3 = fork();
	if (pid_3 == 0)
	{
		// Child process for third cmd
		ft_printf("from the third child process\n");
		close_pipe(pipe_1);
		close(pipe_2[INPUT]);
		dup2(pipe_2[OUTPUT], STDIN);
		dup2(pipe_3[INPUT], STDOUT);
		execve(
			parse_program_path(pipex_data->cmds[2], pipex_data),
			parse_program_args(pipex_data->cmds[2]),
			__environ
		);
	}
	pid_4 = fork();
	if (pid_4 == 0)
	{
		// Child process for the fourth cmd
		ft_printf("from the fourth child process\n");
		close_pipe(pipe_1);
		close_pipe(pipe_2);
		close(pipe_3[INPUT]);
		dup2(pipe_3[OUTPUT], STDIN);
		dup2(pipex_data->outfile, STDOUT);
		execve(
			parse_program_path(pipex_data->cmds[3], pipex_data),
			parse_program_args(pipex_data->cmds[3]),
			__environ
		);
	}
	close_pipe(pipe_1);
	close_pipe(pipe_2);
	close_pipe(pipe_3);
	waitpid(pid_1, NULL, 0);
	waitpid(pid_2, NULL, 0);
	waitpid(pid_3, NULL, 0);
	waitpid(pid_4, NULL, 0);
}
