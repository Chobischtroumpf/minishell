/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 13:19:58 by alessandro        #+#    #+#             */
/*   Updated: 2021/01/04 17:15:23 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**path_array_creation(void)
{
	char	**path_array;
	char	*path_str;
	int		i;
	
	i = -1;
	path_str = ft_find_by_key2("PATH");
	if (ft_strcmp(path_str, ""))
	{
		if (!(path_array = ft_split_empty(path_str, ':')))
			ft_exit_error();
		while (path_array[++i] != NULL)
			if (ft_haschr(path_array[i], -1))
			{
				path_str = path_array[i];
				path_array[i] = ft_strdup(".");
				free (path_str);
			}
	}
	else
	{
		if (!(path_array = malloc(sizeof(char*) * 2)))
			ft_exit_error();
		path_array[0] = ft_strdup(".");
		path_array[1] = NULL;
	}
	
	return (path_array);
}

static void	exec_with_path(t_cmd *cmd, char **path_array, char **env_array)
{
	char	*path_cmd;
	char	*path_cmd2;
	int		i;

	i = 0;
	while (path_array[i])
	{
		path_cmd = ft_strjoin(path_array[i], "/");
		path_cmd2 = ft_strjoin(path_cmd, cmd->argv[0]);
		
		execve(path_cmd2, cmd->argv, env_array);
		free(path_cmd);
		free(path_cmd2);
		i++;
	}
}

int			ft_check_file(char *cmd)
{
	int		ret_val;

	ret_val = ft_file_is_symlink(cmd);
	if (ret_val != 127)
	{
		if (!ft_file_exists(cmd))
			ret_val = ft_err_file_not_found(cmd, NULL, 127);
		else if (ft_file_is_dir(cmd))
			ret_val = ft_err_is_dir(cmd, NULL, 126);
		else if (!ft_file_is_exec(cmd) || !ft_file_readable(cmd))
			ret_val = ft_err_no_access(cmd, NULL, 126);
	}
	return (ret_val);
}

static void	exec_cmd(t_cmd *cmd)
{
	char	**path_array;
	char	**env_array;
	int		ret_val;

	env_array = ft_env_to_array();
	if (!cmd->has_path && (path_array = path_array_creation()))
	{
		
		exec_with_path(cmd, path_array, env_array);
		ft_free_array(env_array);
		ft_free_array(path_array);
		exit(ft_no_cmd_error(cmd->argv[0], 127));
	}
	else
	{
		ret_val = ft_check_file(cmd->argv[0]);
		execve(cmd->argv[0], cmd->argv, env_array);
		exit(ret_val);
	}
}

void		ft_exec_extern(t_cmd *cmd)
{
	int		pid;
	int		status;

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
		if (get_minishell()->excode == 139)
			ft_err_is_segfault(cmd->argv[0], NULL, 0);
	}
}
