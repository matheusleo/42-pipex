/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 12:36:25 by mleonard          #+#    #+#             */
/*   Updated: 2022/11/27 18:08:50 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	error_open(char *file_name)
{
	ft_printf("ERR_FILE: Unable to open '%s' file\n", file_name);
	exit(ERR);
}

int	error_func(char *func_name)
{
	ft_printf("ERR_FUNC: Unable to succeed in '%s' call\n", func_name);
	exit(ERR);
}

int	error_access(char *cmd)
{
	ft_printf("ERR_ACCESS: Unable to access path for '%s' command\n", cmd);
	exit(ERR);
}
