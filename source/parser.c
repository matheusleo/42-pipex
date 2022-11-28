/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 12:25:26 by mleonard          #+#    #+#             */
/*   Updated: 2022/11/28 02:11:45 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static int	get_fd(char *file_name, int flags, t_pipex *pipex_data)
{
	int	fd;

	fd = open(file_name, O_RDWR | flags);
	if (fd == ERR)
		error_open(file_name, pipex_data);
	return (fd);
}

static char	*parse_program_path(char *cmd, t_pipex *pipex_data)
{
	char	**cmd_splitted;
	char	*cmd_path;

	cmd_splitted = ft_split(cmd, ' ');
	cmd_path = ft_strjoin("/bin/", cmd_splitted[0]);
	free_vector(cmd_splitted);
	if (access(cmd_path, X_OK) == ERR)
		error_access(cmd, pipex_data);
	return (cmd_path);
}

t_pipex	*parse_input(char *argv[], t_pipex *pipex_data)
{
	pipex_data->infile = get_fd(argv[1], 0, pipex_data);
	pipex_data->outfile = get_fd(argv[4], O_CREAT | O_TRUNC, pipex_data);
	pipex_data->cmd_1 = ft_split(argv[2], ' ');
	pipex_data->cmd_path_1 = parse_program_path(argv[2], pipex_data);
	pipex_data->cmd_2 = ft_split(argv[3], ' ');
	pipex_data->cmd_path_2 = parse_program_path(argv[3], pipex_data);
	return (pipex_data);
}
