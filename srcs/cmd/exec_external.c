/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 13:19:58 by alessandro        #+#    #+#             */
/*   Updated: 2021/01/21 17:09:06 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_check_file(char *cmd, int is_printed)
{
	int ret_val;

	ret_val = ft_file_is_symlink(cmd);
	if (is_printed && ret_val != 127)
	{
		if (!ft_file_exists(cmd))
			ret_val = ft_err_file_not_found(cmd, NULL, 127);
		else if (ft_file_is_dir(cmd))
			ret_val = ft_err_is_dir(cmd, NULL, 126);
		else if (!ft_file_is_exec(cmd) || !ft_file_readable(cmd))
			ret_val = ft_err_no_access(cmd, NULL, 126);
	}
	else if (ret_val != 127)
	{
		if (!ft_file_exists(cmd))
			ret_val = 127;
		else if (ft_file_is_dir(cmd) || !ft_file_is_exec(cmd) ||
		!ft_file_readable(cmd))
			ret_val = 126;
	}
	return (ret_val);
}

static char	**path_array_creation(char *cmd)
{
	char	**path_array;
	int		i;

	if (ft_strcmp(ft_find_by_key2("PATH"), "") && (i = -1))
	{
		if (!(path_array = ft_split_empty(ft_find_by_key2("PATH"), ':')))
			ft_exit_error();
		while (path_array[++i] != NULL)
			if (ft_haschr(path_array[i], -1))
			{
				free(path_array[i]);
				if (!(path_array[i] = ft_strdup(".")))
					ft_exit_error();
			}
	}
	else
	{
		if (ft_check_file(cmd, 0))
			return (NULL);
		if (!(path_array = ft_calloc(2, sizeof(char *))))
			ft_exit_error();
		if (!(path_array[0] = ft_strdup(".")))
			ft_exit_error();
	}
	return (path_array);
}

static int	exec_with_path(t_cmd *cmd, char **path_array, char **env_array)
{
	char	*path_cmd;
	char	*path_cmd2;
	int		i;

	i = 0;
	while (path_array[i])
	{
		if (!(path_cmd = ft_strjoin(path_array[i], "/")))
			return (132);
		if (!(path_cmd2 = ft_strjoin(path_cmd, cmd->argv[0])))
			return (free_str_ret(path_cmd, 132));
		if (execve(path_cmd2, cmd->argv, env_array) == -1)
			if (ft_file_exists(path_cmd2) && !ft_file_is_exec(path_cmd2))
				return (ft_err_no_access(path_cmd2, NULL, 126));
		free(path_cmd);
		path_cmd = NULL;
		free(path_cmd2);
		path_cmd2 = NULL;
		i++;
	}
	return (0);
}

void		exec_cmd(t_cmd *cmd)
{
	char	**path_array;
	char	**env_array;
	int		ret_val;

	if (!(env_array = ft_env_to_array()))
		ft_exit_error();
	if (!cmd->has_path && (path_array = path_array_creation(cmd->argv[0])))
	{
		ret_val = exec_with_path(cmd, path_array, env_array);
		ft_free_array(env_array, 0);
		ft_free_array(path_array, 0);
		if (ret_val)
			exit(ret_val);
		exit(ft_no_cmd_error(cmd->argv[0], 127));
	}
	else
	{
		ret_val = ft_check_file(cmd->argv[0], 1);
		execve(cmd->argv[0], cmd->argv, env_array);
		exit(ret_val);
	}
}

void		ft_exec_extern(t_cmd *cmd)
{
	int pid;
	int status;

	if (ft_haschr(cmd->argv[0], '/'))
		cmd->has_path = 1;
	if ((pid = fork()) == -1)
		ft_exit_error();
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		exec_cmd(cmd);
	}
	else if (pid > 0)
	{
		wait(&status);
		ft_get_exit_code(status, NO_EXCODE);
		if (get_minishell()->exval == 139)
			ft_err_is_segfault(cmd->argv[0], NULL, 0);
	}
}
