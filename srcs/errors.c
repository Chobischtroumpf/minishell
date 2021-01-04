/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 13:43:46 by adorigo           #+#    #+#             */
/*   Updated: 2020/12/18 00:44:15 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_error_dispatch(int ret_val, char *cmd, char *arg)
{
	if (errno == EFAULT)
		ret_val = 11;
	else if (errno == ENOENT)
		ft_err_file_not_found(cmd, arg, 127);
	else if (errno == EISDIR)
		ft_err_is_dir(cmd, arg, 0);
	else if (errno == EACCES)
		ft_err_no_access(cmd, arg, 0);
	else if (errno == ENAMETOOLONG)
		ft_err_file_too_long(cmd, arg);
	else if (errno == ELOOP)
		ft_err_loop(cmd, arg);
	else
		ret_val = 0;
	errno = 0;
	return (ret_val);
}

int		ft_no_cmd_error(char *cmd, int ret)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (ret);
}

/*
** the numeric_arg_error function prints the numeric_arg_error to stderr
*/

void	ft_numeric_arg_error(char *cmd, char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

/*
** the too_many_args function prints to stderr the fact that there are too many
** arguments in the command
*/

int		ft_too_many_args(char *cmd, int ret)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": too many arguments\n", 2);
	return (ret);
}

/*
** the parse_error function prints to stderr the fact that there is an error in
** the line
*/

int		ft_parse_error(char *error, int ret)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("'\n", 2);
	return (ret);
}
