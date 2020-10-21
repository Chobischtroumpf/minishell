/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 13:43:46 by adorigo           #+#    #+#             */
/*   Updated: 2020/10/21 15:58:53 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** the numeric_arg_error function prints the numeric_arg_error to stderr
*/

int		ft_numeric_arg_error(char *cmd, char *arg, int ret)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(":", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("numeric argument required\n", 2);
	return (ret);
}

/*
** the too_many_args function prints to stderr the fact that there are too many
** arguments in the command
*/

int		ft_too_many_args(char *cmd, int ret)
{
	ft_putstr_fd("minishell: too many arguments: %s\n", 2);
	ft_putstr_fd(cmd, 2);
	return (ret);
}

/*
** the parse_error function prints to stderr the fact that there is an error in
** the line
*/

int		ft_parse_error(char *error, int ret)
{
	ft_putstr_fd("minishell: parse error near", 2);
	ft_putstr_fd(error, 2);
	return (ret);
}

/*
** the exit_error function frees the minishell struct, assigns errno to strerr
** and prints strerr to the stderr
*/

void	*ft_exit_error(void)
{
	char *strerr;

	ft_free_cmd();
	strerr = strerror(errno);
	ft_putstr_fd(strerr, 2);
	exit(-1);
	return (NULL);
}
