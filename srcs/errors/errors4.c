/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 15:14:46 by alessandro        #+#    #+#             */
/*   Updated: 2021/01/13 12:18:41 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_err_is_dir(char *cmd, char *arg, int ret)
{
	ft_putstr_fd("minishell", 2);
	if (cmd)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(cmd, 2);
	}
	if (arg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(arg, 2);
	}
	ft_putstr_fd(": is a directory\n", 2);
	return (ret);
}

int		ft_err_not_exec(char *cmd, char *arg, int ret)
{
	ft_putstr_fd("minishell", 2);
	if (cmd)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(cmd, 2);
	}
	if (arg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(arg, 2);
	}
	ft_putstr_fd(": pouet\n", 2);
	return (ret);
}

int		ft_err_is_segfault(char *cmd, char *arg, int ret)
{
	ft_putstr_fd("segmentation fault (core dumped) ", 2);
	if (cmd)
		ft_putstr_fd(cmd, 2);
	if (arg)
	{
		ft_putstr_fd(" ", 2);
		ft_putstr_fd(arg, 2);
	}
	ft_putstr_fd("\n", 2);
	return (ret);
}

int		ft_err_is_symlink_loop(char *cmd, int ret_val)
{
	ft_putstr_fd("minishell: too many levels of symbolic links: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	return (ret_val);
}

int		ft_err_redirect(char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	return (0);
}
