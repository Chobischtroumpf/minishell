/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 16:35:02 by alessandro        #+#    #+#             */
/*   Updated: 2021/01/06 23:17:56 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_file_readable(char *cmd)
{
	struct stat stats;

	if (stat(cmd, &stats) == 0)
	{
		if (stats.st_mode & S_IRUSR)
			return (1);
	}
	return (0);
}

int			ft_file_is_exec(char *cmd)
{
	struct stat stats;

	if (stat(cmd, &stats) == 0)
	{
		if (stats.st_mode & S_IXUSR)
			return (1);
	}
	return (0);
}

int			ft_file_is_dir(char *cmd)
{
	struct stat stats;

	if (stat(cmd, &stats) == 0)
	{
		if (stats.st_mode & IS_DIR)
			return (1);
	}
	return (0);
}

int			ft_file_exists(char *cmd)
{
	struct stat stats;

	if (stat(cmd, &stats) == 0)
		return (1);
	return (0);
}

int			ft_file_is_symlink(char *cmd)
{
	struct stat stats;

	if (stat(cmd, &stats) == 0)
	{
		if (stats.st_mode & IS_DIR)
			return (0);
	}
	else
	{
		if (errno == ELOOP)
			return (ft_err_is_symlink_loop(cmd, 127));
	}
	return (0);
}
