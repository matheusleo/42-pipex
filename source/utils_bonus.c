/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 16:40:30 by mleonard          #+#    #+#             */
/*   Updated: 2022/11/29 01:26:44 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

int	get_fd(char *file_name, int flags, t_pipex *pipex_data)
{
	int	fd;

	fd = open(file_name, O_RDWR | flags);
	if (fd == ERR)
		error_open(file_name, pipex_data);
	return (fd);
}

void	free_vector(char **splitted)
{
	int	idx;

	idx = 0;
	while (splitted[idx])
		free(splitted[idx++]);
	free(splitted);
}
