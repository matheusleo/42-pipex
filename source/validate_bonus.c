/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 12:11:36 by mleonard          #+#    #+#             */
/*   Updated: 2022/11/27 12:29:01 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	validate_input(int argc)
{
	if (argc != 5)
	{
		ft_printf("ERR: input does not attend the requirements\n");
		ft_printf("Expected to be: <infile> '<cmd1>' '<cmd2>' <outfile>\n");
		exit (ERR);
	}
	return (OK);
}
