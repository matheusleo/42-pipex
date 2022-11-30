/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 12:25:26 by mleonard          #+#    #+#             */
/*   Updated: 2022/11/29 01:42:15 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

static char	**parse_commands(int argc, char *argv[], t_pipex *pipex_data)
{
	char	**commands;
	int		counter;

	counter = 0;
	commands = (char **)malloc(sizeof(char *) * (argc - 3));
	while (counter < argc - 3)
		commands[counter++] = argv[counter + 2];
	pipex_data->cmds = commands;
	pipex_data->cmds_len = counter;
}

char	**parse_program_args(char *cmd)
{
	char	**command;

	command = ft_split(cmd, ' ');
	return (command);
}

char	*parse_program_path(char *cmd, t_pipex *pipex_data)
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

t_pipex	*parse_input(int argc, char *argv[], t_pipex *pipex_data)
{
	pipex_data->infile = get_fd(argv[1], 0, pipex_data);
	pipex_data->outfile = get_fd(argv[argc - 1], O_CREAT | O_TRUNC, pipex_data);
	parse_commands(argc, argv, pipex_data);
	pipex_data->pids = (int *)malloc(sizeof(int) * pipex_data->cmds_len);
	return (pipex_data);
}
