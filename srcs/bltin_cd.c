/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 13:00:29 by nathan            #+#    #+#             */
/*   Updated: 2021/01/06 23:24:47 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(void)
{
	char pwd[PATH_MAX];
	char *oldpwd;

	if (ft_find_by_key2("PWD"))
		oldpwd = ft_strdup(ft_find_by_key2("PWD"));
	else
		oldpwd = ft_strdup("");
	getcwd(pwd, sizeof(pwd));
	ft_remove_env(&get_minishell()->env, "PWD");
	ft_remove_env(&get_minishell()->env, "OLDPWD");
	ft_add_env2("OLDPWD", oldpwd);
	ft_add_env2("PWD", pwd);
	free(oldpwd);
}

int		ft_array_size(char **array)
{
	int i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int		ft_chdir_err(int err_code, char *cmd, char *arg)
{
	if (errno == ENOENT)
		ft_err_file_not_found(cmd, arg, 0);
	else if (errno == EACCES)
		ft_err_no_access(cmd, arg, 0);
	else if (errno == ENOTDIR)
		ft_err_not_dir(cmd, arg);
	else if (errno == ENAMETOOLONG)
		ft_err_file_too_long(cmd, arg);
	else if (errno == ELOOP)
		ft_err_loop(cmd, arg);
	errno = 0;
	return (-err_code);
}

void	init_home(void)
{
	if (!ft_find_by_key2("OLDPWD"))
		ft_add_env2("OLDPWD", "");
	if (!ft_find_by_key2("HOME"))
		ft_add_env2("HOME", "");
}

int		ft_exec_cd(t_cmd *cmd)
{
	char	*home;
	int		ret;

	ret = 1;
	init_home();
	if (!(home = ft_strdup(ft_find_by_key2("HOME"))))
		ft_putstr_fd("minishell: cd: HOME not set", 2);
	else if (ft_array_size(cmd->argv) > 2)
		return (ft_too_many_args("cd", 1));
	else if (ft_array_size(cmd->argv) == 1)
	{
		if (!ft_strncmp(home, "", ft_strlen(home)))
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		else
			ret = ft_chdir_err(chdir(home), cmd->argv[0], "home");
	}
	else if (!(ft_strncmp(cmd->argv[1], "", ft_strlen(cmd->argv[1]))))
		ret = ft_chdir_err(chdir("."), cmd->argv[0], cmd->argv[1]);
	else if (!(ft_strncmp(cmd->argv[1], "~", ft_strlen(cmd->argv[1]))))
		ret = ft_chdir_err(chdir(home), cmd->argv[0], cmd->argv[1]);
	else if (!(ft_strncmp(cmd->argv[1], "-", ft_strlen(cmd->argv[1]))))
		ret = ft_chdir_err(chdir(ft_find_by_key2("OLDPWD")),\
											cmd->argv[0], cmd->argv[1]);
	else if ((ft_array_size(cmd->argv) == 2))
		ret = ft_chdir_err(chdir(cmd->argv[1]), cmd->argv[0], cmd->argv[1]);
	if (!ret)
		update_pwd();
	free(home);
	return (ret);
}
