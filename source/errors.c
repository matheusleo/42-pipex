/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 12:36:25 by mleonard          #+#    #+#             */
/*   Updated: 2022/11/27 12:39:23 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	error_func(char *func_name)
{
	ft_printf("ERR_FUNC: Unable to succed in '%s' call\n", func_name);
	exit(ERR);
}
