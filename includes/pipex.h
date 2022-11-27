/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 18:24:53 by mleonard          #+#    #+#             */
/*   Updated: 2022/11/27 18:52:27 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <libft.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_pipex
{
	int		infile;
	char	**cmd_1;
	char	*cmd_path_1;
	char	**cmd_2;
	char	*cmd_path_2;
	int		outfile;
	int		status;
	int		pipe[2];
}				t_pipex;

// I/O macros
# define STDIN 0
# define STDOUT 1

// Macros related to error status
# define ERR -1
# define OK 0

// Macros related to the pipe ends
# define OUTPUT 0
# define INPUT 1

// Validate user input functions
int		validate_input(int argc);

// Parser related functions
t_pipex	*parse_input(char *argv[], t_pipex *pipex_data);

// Error handlers
void	error_open(char *file_name, t_pipex *pipex_data);
void	error_func(char *func_name, t_pipex *pipex_data);
void	error_access(char *cmd, t_pipex *pipex_data);

// Main functions
int		pipex(t_pipex *pipex_data);
int		shutdown_pipex(t_pipex *pipex_data);

// Utils functions
void	free_vector(char **splitted);

#endif
