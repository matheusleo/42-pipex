/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 12:25:26 by mleonard          #+#    #+#             */
/*   Updated: 2022/11/27 15:12:07 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static int	get_fd(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDWR);
	if (fd == ERR)
		error_func("open");
	return (fd);
}

static char	*parse_program_path(char *cmd)
{
	char	**cmd_splitted;
	char	*cmd_path;
	int		counter;

	counter = 0;
	cmd_splitted = ft_split(cmd, ' ');
	cmd_path = ft_strjoin("/bin/", cmd_splitted[0]);
	while (cmd_splitted[counter])
		free(cmd_splitted[counter++]);
	free(cmd_splitted);
	return (cmd_path);
}

t_pipex	*parse_input(char *argv[], t_pipex *pipex_data)
{
	pipex_data->infile = get_fd(argv[1]);
	pipex_data->cmd_1 = argv[2];
	pipex_data->cmd_path_1 = parse_program_path(argv[2]);
	pipex_data->cmd_2 = argv[3];
	pipex_data->cmd_path_2 = parse_program_path(argv[3]);
	pipex_data->outfile = get_fd(argv[4]);
	return (pipex_data);
}
