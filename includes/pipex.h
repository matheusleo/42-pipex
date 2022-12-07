/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 18:24:53 by mleonard          #+#    #+#             */
/*   Updated: 2022/12/06 21:32:32 by mleonard         ###   ########.fr       */
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
	char	**cmds;
	int		cmds_len;
	int		outfile;
	int		status;
	int		*pids;
	int		pipes[2][2];
	int		here_doc;
	char	*limiter;
	int		limiter_len;
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
int		validate_input(int argc, char *argv[]);

// Parser related functions
t_pipex	*parse_input(int argc, char *argv[], t_pipex *pipex_data);
char	*parse_program_path(char *cmd, t_pipex *pipex_data);
char	**parse_program_args(char *cmd);
t_pipex	*parse_here_doc(int argc, char *argv[], t_pipex *pipex_data);

// Error handlers
void	error_open(char *file_name, t_pipex *pipex_data);
void	error_func(char *func_name, t_pipex *pipex_data);
void	error_access(char *cmd, t_pipex *pipex_data);

// Main functions
int		pipex(t_pipex *pipex_data);
int		here_doc(t_pipex *pipex_data);
int		shutdown_pipex(t_pipex *pipex_data);

// Utils functions
int		get_fd(char *file_name, int flags, t_pipex *pipex_data);
void	free_vector(char **splitted);
int		create_child(t_pipex *pipex_data);
void	close_pipe(int pipe[2]);
char	*remove_all(char *str, int old);
char	*mask_spaces(char *cmd);
char	*unmask_spaces(char *cmd);

#endif
