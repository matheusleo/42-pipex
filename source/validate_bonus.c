/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 12:11:36 by mleonard          #+#    #+#             */
/*   Updated: 2022/11/29 00:36:08 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

int	validate_input(int argc)
{
	if (argc < 5)
	{
		ft_printf("ERR: input does not attend the requirements\n");
		ft_printf("Expected to be: <infile> '<cmd1>' '<cmd2>'");
		ft_printf("'<cmdN>' ... <outfile>\n");
		exit (ERR);
	}
	return (OK);
}
