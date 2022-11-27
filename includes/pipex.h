/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 18:24:53 by mleonard          #+#    #+#             */
/*   Updated: 2022/11/27 11:41:03 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <libft.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>

// I/O macros
# define STDIN 0
# define STDOUT 1

// Macros related to error status
# define ERR -1
# define OK 0

#endif
