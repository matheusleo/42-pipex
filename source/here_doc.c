/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 21:59:32 by mleonard          #+#    #+#             */
/*   Updated: 2022/12/07 02:59:11 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static int	get_literal_doc(t_pipex *pipex_data)
{
	char	**line;

	while (TRUE)
	{
		ft_printf("pipex$> ");
		line = get_next_line_2(STDOUT);
		if (ft_strncmp(line[0],
				pipex_data->limiter,
				ft_strlen(pipex_data->limiter)
			) == 0 && line[0][pipex_data->limiter_len] == '\n')
			return (free (line[0]), free(line[1]), free(line), OK);
		ft_putstr_fd(line[0], pipex_data->pipes[0][INPUT]);
		free(line[0]);
		free(line);
	}
}

static void	init_pipes(t_pipex *pipex_data)
{
	if (pipe(pipex_data->pipes[0]) == ERR)
		error_func("pipe", pipex_data);
	if (pipe(pipex_data->pipes[1]) == ERR)
		error_func("pipe", pipex_data);
}

static void	redirect_input_output(t_pipex *pipex_data, int cur_pid)
{
	close(pipex_data->pipes[cur_pid % 2][INPUT]);
	dup2(pipex_data->pipes[cur_pid % 2][OUTPUT], STDIN);
	if (cur_pid == pipex_data->cmds_len - 1)
		dup2(pipex_data->outfile, STDOUT);
	else
		dup2(pipex_data->pipes[(cur_pid + 1) % 2][INPUT], STDOUT);
}

int	here_doc(t_pipex *pipex_data)
{
	int		pid_idx;

	pid_idx = 0;
	init_pipes(pipex_data);
	get_literal_doc(pipex_data);
	while (pid_idx < pipex_data->cmds_len)
	{
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
		close_pipe(pipex_data->pipes[pid_idx % 2]);
		waitpid(pipex_data->pids[pid_idx], NULL, 0);
		pid_idx++;
	}
	return (OK);
}
