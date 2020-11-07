/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 13:00:29 by nathan            #+#    #+#             */
/*   Updated: 2020/11/07 17:57:08 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int ft_array_size(char **array)
{
	int i;

	i = 0;
	while(array[i])
		i++;
	return (i);
}

int	ft_chdir_err(int err_code, char *arg)
{
	
	if(err_code == ENOENT)
		ft_file_not_found(arg);
	else if(err_code == EACCES)
		ft_putstr("pas d'acces");
	printf("ERRCODE = %d\n", err_code);
	return (EXIT_FAILURE);
}

int ft_exec_cd(t_cmd *cmd)
{
	char *home;
	printf("CMD SIZE %d\n", ft_array_size(cmd->argv));
	if (!(home = ft_strdup(ft_find_by_key2("HOME"))))
		home = ft_strdup("/home");
	else if (ft_array_size(cmd->argv) > 2)
		return (ft_too_many_args("cd", 1));
	else if (ft_array_size(cmd->argv) == 1)
		return(chdir(home));
	else if (!(ft_strncmp(cmd->argv[1], "~", ft_strlen(cmd->argv[1]))))
		return(chdir(home));
	else if (!(ft_strncmp(cmd->argv[1], "-", ft_strlen(cmd->argv[1]))))
		return (ft_chdir_err(chdir(ft_find_by_key2("OLDPWD")), cmd->argv[1]));
	else if ((chdir(cmd->argv[1])) < 0)
		return (ft_chdir_err(chdir(cmd->argv[1]), cmd->argv[1]));
	update_pwd();
	free(home);
	return (EXIT_SUCCESS);
}