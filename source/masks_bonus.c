/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 01:19:33 by mleonard          #+#    #+#             */
/*   Updated: 2022/12/06 01:39:24 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

static void	replace(char *ptr, int c, int pos)
{
	ptr[pos] = c;
}

char	*mask_spaces(char *cmd)
{
	size_t	idx;
	int		between_quotes;
	char	*cmd_cpy;

	idx = 0;
	between_quotes = FALSE;
	cmd_cpy = ft_strdup(cmd);
	while (cmd[idx])
	{
		if (cmd[idx] == '\'')
			between_quotes = !between_quotes;
		if (between_quotes && cmd_cpy[idx] == ' ')
			replace(cmd_cpy, 31, idx);
		idx++;
	}
	return (cmd_cpy);
}

char	*unmask_spaces(char *cmd)
{
	size_t	idx;

	idx = 0;
	while (cmd[idx])
	{
		if (cmd[idx] == 31)
			replace(cmd, ' ', idx);
		idx++;
	}
	return (cmd);
}
