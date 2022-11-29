/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 16:40:30 by mleonard          #+#    #+#             */
/*   Updated: 2022/11/29 00:36:08 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

void	free_vector(char **splitted)
{
	int	idx;

	idx = 0;
	while (splitted[idx])
		free(splitted[idx++]);
	free(splitted);
}
