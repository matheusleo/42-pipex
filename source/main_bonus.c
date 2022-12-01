/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 18:24:46 by mleonard          #+#    #+#             */
/*   Updated: 2022/11/30 01:58:02 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

static t_pipex	init_pipex_struct(void)
{
	t_pipex	data;

	data.infile = 0;
	data.cmds = NULL;
	data.cmds_len = 0;
	data.outfile = 1;
	data.status = OK;
	data.pids = NULL;
	data.pipes[0][0] = 1;
	data.pipes[0][1] = 0;
	data.pipes[1][0] = 1;
	data.pipes[1][1] = 0;
	data.here_doc = FALSE;
	data.limiter = NULL;
	return (data);
}

int	shutdown_pipex(t_pipex *pipex_data)
{
	if (pipex_data->cmds)
		free(pipex_data->cmds);
	if (pipex_data->pids)
		free(pipex_data->pids);
	close(pipex_data->infile);
	close(pipex_data->outfile);
	exit(pipex_data->status);
}

int	main(int argc, char *argv[])
{
	t_pipex	pipex_data;

	validate_input(argc, argv);
	pipex_data = init_pipex_struct();
	parse_input(argc, argv, &pipex_data);
	pipex(&pipex_data);
	pipex_data.status = OK;
	shutdown_pipex(&pipex_data);
}
