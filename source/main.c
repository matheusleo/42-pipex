/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 18:24:46 by mleonard          #+#    #+#             */
/*   Updated: 2022/11/28 01:50:06 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static t_pipex	init_pipex_struct(void)
{
	t_pipex	data;

	data.infile = 0;
	data.cmd_1 = NULL;
	data.cmd_path_1 = NULL;
	data.cmd_2 = NULL;
	data.cmd_path_2 = NULL;
	data.outfile = 1;
	data.status = OK;
	data.pipe[0] = 0;
	data.pipe[1] = 0;
	return (data);
}

int	shutdown_pipex(t_pipex *pipex_data)
{
	if (pipex_data->cmd_1)
		free_vector(pipex_data->cmd_1);
	if (pipex_data->cmd_2)
		free_vector(pipex_data->cmd_2);
	if (pipex_data->cmd_path_1)
		free(pipex_data->cmd_path_1);
	if (pipex_data->cmd_path_2)
		free(pipex_data->cmd_path_2);
	close(pipex_data->infile);
	close(pipex_data->outfile);
	exit(pipex_data->status);
}

int	main(int argc, char *argv[])
{
	t_pipex	pipex_data;

	validate_input(argc);
	pipex_data = init_pipex_struct();
	parse_input(argv, &pipex_data);
	pipex(&pipex_data);
	pipex_data.status = OK;
	shutdown_pipex(&pipex_data);
}
