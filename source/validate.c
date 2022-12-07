/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 12:11:36 by mleonard          #+#    #+#             */
/*   Updated: 2022/12/06 21:32:38 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	validate_input(int argc, char *argv[])
{
	if (ft_strncmp(argv[1], "here_doc", 8) == 0 && argc != 6)
	{
		ft_printf("ERR: input does not attend the requirements\n");
		ft_printf("Expected to be:\n	");
		ft_printf("./pipex here_doc LIMITER '<cmd1>' '<cmd2>' <outfile>\n");
		exit (ERR);
	}
	else if (argc < 5)
	{
		ft_printf("ERR: input does not attend the requirements\n");
		ft_printf("Expected to be: \n	");
		ft_printf("./pipex <infile> '<cmd1>' '<cmd2>' ... '<cmdN>' <outfile>\n");
		ft_printf("	OR ./pipex here_doc LIMITER '<cmd1>' '<cmd2>' <outfile>\n");
		exit (ERR);
	}
	return (OK);
}
