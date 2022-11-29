/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 12:36:25 by mleonard          #+#    #+#             */
/*   Updated: 2022/11/29 00:36:08 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

void	error_open(char *file_name, t_pipex *pipex_data)
{
	ft_printf("ERR_FILE: Unable to open '%s' file\n", file_name);
	pipex_data->status = ERR;
	shutdown_pipex(pipex_data);
}

void	error_func(char *func_name, t_pipex *pipex_data)
{
	ft_printf("ERR_FUNC: Unable to succeed in '%s' call\n", func_name);
	pipex_data->status = ERR;
	shutdown_pipex(pipex_data);
}

void	error_access(char *cmd, t_pipex *pipex_data)
{
	ft_printf("ERR_ACCESS: Unable to access path for '%s' command\n", cmd);
	pipex_data->status = ERR;
	shutdown_pipex(pipex_data);
}
