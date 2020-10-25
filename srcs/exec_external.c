/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 13:19:58 by alessandro        #+#    #+#             */
/*   Updated: 2020/10/25 09:16:37 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **path_array_creation(void)
{
	t_list	*env;
	char *path_env;
	char **path_array;

	env = get_minishell()->env;
	while (env)
	{
		if (!ft_strcmp(((t_env*)env->key), "PATH"))
			path_array = ft_split(((t_env*)env->value), ":");
		env->next;
	}
	if (!path_array)
		return (0);
	return (path_array);
}

static void	exec_with_path(t_cmd *cmd, char **path_array)
{
	char	*path_cmd;
	char	*path_cmd2;
	char	**arr_env;
	int 	i;

	i = 0;
	arr_env = ;
	while (path_array[i])
	{
		path_cmd = ft_strjoin(path_array[i], "/");
		path_cmd2 = ft_strjoin(path_cmd, cmd->argv[0]);
		execve(path_cmd2, cmd->argv, arr_env);
		ft_free_array();
		free(path_cmd);
		free(path_cmd2);
		i++;
	}
}

static void	exec_cmd(t_cmd *cmd)
{
	char **path_array;

	if (!cmd->has_path && (path_array = path_array_creation()))
	{
		exec_with_path(cmd, path_array);
		exit(ft_no_cmd_error(cmd->argv[0], 127));
	}
	else
		execve(cmd->argv[0], cmd->argv, );
		exit(0);
}

void		ft_exec_extern(t_cmd *cmd)
{
	int pid;
	int status;

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
	}
}