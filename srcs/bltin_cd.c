/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 13:00:29 by nathan            #+#    #+#             */
/*   Updated: 2020/11/07 15:08:16 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <time.h>

void update_pwd(void)
{
	char pwd[PATH_MAX];
	char *oldpwd;

	oldpwd = ft_strdup(ft_find_by_key2("PWD"));
	getcwd(pwd, sizeof(pwd));
	ft_remove_env(&get_minishell()->env, "PWD");
	ft_remove_env(&get_minishell()->env, "OLDPWD");
	ft_add_env2("OLDPWD", oldpwd);
	ft_add_env2("PWD", pwd);
	free(oldpwd);
}

char *ft_crop_path(char **path)
{
	int i;
	char *next_step;
	char *tmp;

	i = 0;
	tmp = ft_strdup(*path);
	next_step = NULL;
	if (**path)
	{
		printf("\n----------------------\nin crop : PATH = %s\n", *path);
		while (*(*path + i) && *(*path + i) != '/')
		{
			printf("path[i] = %c\n", *(*path + i));
			i++;
		}
		printf("I = %d\n----------------------\n", i);
		next_step = ft_substr(*path, 0, i);
		*path = ft_substr(tmp, i + 1, ft_strlen(tmp) - i);
	}
	free(tmp);
	return (next_step);
}

void ft_relative_path(char *arg)
{
	char *pwd;
	char *path;
	char *next_step;

	path = ft_strdup(arg);
	pwd = ft_find_by_key2("PWD");
	next_step = ft_crop_path(&path);
	while (next_step)
	{
		update_pwd();
		if (!ft_strncmp(next_step, ".", ft_strlen(arg)))
			printf("stay\n");
		else if (!ft_strncmp(next_step, "..", ft_strlen(arg)))
			printf("go to parent\n");

		printf("PATH = %s\nNEXT = %s\n", path, next_step);
		next_step = ft_crop_path(&path);
	}
	update_pwd();
}

int ft_exec_cd(t_cmd *cmd)
{
	char *home;
	printf("ARG = %s\n", cmd->argv[1]);
	if (!(home = ft_strdup(ft_find_by_key2("HOME"))))
		home = ft_strdup("/home");
	else if (cmd->argv[2])
		return (ft_too_many_args("cd", 1));
	else if (!cmd->argv[1])
	{
		printf("go home\n");
		chdir(home);
		update_pwd();
		return (EXIT_SUCCESS);
	}
	else if (!ft_strncmp(cmd->argv[1], "-", ft_strlen(cmd->argv[1])))
		ft_printf("go back\n");
	else if (!ft_strncmp(cmd->argv[1], ".", ft_strlen(cmd->argv[1])))
		ft_printf("stay\n");
	else if (!ft_strncmp(cmd->argv[1], "..", ft_strlen(cmd->argv[1])))
		ft_printf("go to parent\n");
	else if (!(chdir(cmd->argv[1])))
	{
		update_pwd();
		printf("chdir worked\n");
		return (EXIT_SUCCESS);
	}
	else
		ft_relative_path(cmd->argv[1]);
	free(home);
	return (EXIT_SUCCESS);
}