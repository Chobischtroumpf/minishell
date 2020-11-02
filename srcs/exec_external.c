/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 13:19:58 by alessandro        #+#    #+#             */
/*   Updated: 2020/11/01 14:54:22 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**path_array_creation(void)
{
	t_env	*env;
	char	**path_array;

	env = get_minishell()->env;
	while (env)
	{
		if (!ft_strcmp(env->key, "PATH"))
			path_array = ft_split(env->value, ':');
		env = env->next;
	}
	if (!path_array)
		ft_exit_error();
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

static void	exec_cmd(t_cmd *cmd)
{
	char	**path_array;
	char	**env_array;

	env_array = ft_env_to_array();
	if (!cmd->has_path && (path_array = path_array_creation()))
	{
		exec_with_path(cmd, path_array, env_array);
		ft_free_array(env_array);
		exit(ft_no_cmd_error(cmd->argv[0], 127));
		ft_free_array(path_array);
	}
	else
	{
		execve(cmd->argv[0], cmd->argv, env_array);
		exit(ft_no_file_error(cmd->argv[0], NULL, 127));
	}
}

void		ft_exec_extern(t_cmd *cmd)
{
	int		pid;
	int		status;

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
	}
}
