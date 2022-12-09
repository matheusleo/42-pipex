/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 12:11:36 by mleonard          #+#    #+#             */
/*   Updated: 2022/12/08 21:06:40 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static int	check_empty_arguments(char *argv[])
{
	int	idx;

	idx = 0;
	while (argv[idx])
	{
		if (!ft_strlen(argv[idx++]))
			return (ERR);
	}
	return (OK);
}

int	validate_input(int argc, char *argv[])
{
	if (check_empty_arguments(argv) == ERR)
	{
		ft_printf("ERR_INPUT: malformatted input was passed to the program\n");
		exit(ERR);
	}
	if (argc < 5)
	{
		ft_printf("ERR: input does not attend the requirements\n");
		ft_printf("Expected to be: \n	");
		ft_printf("./pipex <infile> '<cmd1>' '<cmd2>' ... '<cmdN>' <outfile>\n");
		ft_printf("	OR ./pipex here_doc LIMITER '<cmd1>' '<cmd2>' <outfile>\n");
		exit (ERR);
	}
	return (OK);
}
