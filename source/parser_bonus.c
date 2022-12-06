/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 12:25:26 by mleonard          #+#    #+#             */
/*   Updated: 2022/12/06 01:20:28 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

static void	parse_commands(int argc, char *argv[], t_pipex *pipex_data)
{
	char	**commands;
	int		counter;

	counter = 0;
	commands = (char **)malloc(sizeof(char *) * (argc - 3));
	while (counter < argc - 3)
	{
		commands[counter] = argv[counter + 2];
		counter++;
	}
	pipex_data->cmds = commands;
	pipex_data->cmds_len = counter;
}

char	**parse_program_args(char *cmd)
{
	char	**command;
	char	*cmd_masked;
	int		idx_word;

	idx_word = 0;
	cmd_masked = mask_spaces(cmd);
	command = ft_split(cmd_masked, ' ');
	free(cmd_masked);
	while (command[idx_word])
		unmask_spaces(command[idx_word++]);
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

t_pipex	*parse_here_doc(int argc, char *argv[], t_pipex *pipex_data)
{
	pipex_data->here_doc = TRUE;
	pipex_data->cmds = (char **)malloc(sizeof(char *) * 2);
	pipex_data->cmds[0] = argv[3];
	pipex_data->cmds[1] = argv[4];
	pipex_data->cmds_len = 2;
	pipex_data->pids = (int *)malloc(sizeof(int) * 2);
	pipex_data->limiter = argv[2];
	pipex_data->limiter_len = ft_strlen(argv[2]);
	pipex_data->infile = STDIN;
	pipex_data->outfile = get_fd(argv[argc - 1], O_CREAT | O_TRUNC, pipex_data);
	return (pipex_data);
}

t_pipex	*parse_input(int argc, char *argv[], t_pipex *pipex_data)
{
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		return (parse_here_doc(argc, argv, pipex_data));
	pipex_data->infile = get_fd(argv[1], 0, pipex_data);
	pipex_data->outfile = get_fd(argv[argc - 1], O_CREAT | O_TRUNC, pipex_data);
	parse_commands(argc, argv, pipex_data);
	pipex_data->pids = (int *)malloc(sizeof(int) * pipex_data->cmds_len);
	return (pipex_data);
}
