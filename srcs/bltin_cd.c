/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 13:00:29 by nathan            #+#    #+#             */
/*   Updated: 2020/11/06 19:13:14 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(void)
{
	char 	pwd[PATH_MAX];
	char	*oldpwd;
	
	oldpwd = ft_strdup(ft_find_by_key2("PWD"));
	getcwd(pwd, sizeof(pwd));
	printf("PWD = %s", pwd);
	ft_remove_env(&get_minishell()->env, "PWD");
	ft_remove_env(&get_minishell()->env, "OLDPWD");
	ft_add_env2("OLDPWD", oldpwd);
	ft_add_env2("PWD", pwd);
	free(oldpwd);
}

void	ft_relative_path(char *arg)
{
	// char *absolute;
	if (!ft_strncmp(arg, ".", ft_strlen(arg)))
		printf("stay\n");
	else if (!ft_strncmp(arg, "..", ft_strlen(arg)))
		printf("go back\n");
	update_pwd();
	// else 
	// 	printf("zut\n");		
}

int		ft_exec_cd(t_cmd *cmd)
{
	char *home;
	
	if (!(home = ft_strdup(ft_find_by_key2("HOME"))))
		home = "/home";
	else if (cmd->argv[2])
		return(ft_too_many_args("cd", 1));
	else if (!cmd->argv[1])
	{
		printf("hello\n");
		chdir(home);
		update_pwd();
		return(EXIT_SUCCESS);
	}
	
	if (chdir(cmd->argv[1]) < 0)
	{
		update_pwd();
		ft_printf("file not found\n");
		return (1);
	}
	else
		ft_relative_path(cmd->argv[1]);
	free(home);
	return (EXIT_SUCCESS);
}