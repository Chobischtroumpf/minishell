/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 12:08:19 by adorigo           #+#    #+#             */
/*   Updated: 2020/03/14 14:13:23 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_exec_pwd(void)
{
	char cwd[PATH_MAX];

	if (!(getcwd(cwd, sizeof(cwd))))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	ft_printf("%s\n", cwd);
	return (1);
}

// int ft_exec_echo(t_minishell *minishell);

int ft_exec_exit(void)
{
	ft_free_all();
	return (1);
}

static int ft_exec_builtin(int bltin_pos, t_minishell *minishell)
{
	if (bltin_pos == 0)
		return (ft_exec_echo(minishell));
	if (bltin_pos == 1)
		return(ft_exec_cd(minishell->tokens));
	if (bltin_pos == 2)
		return(ft_exec_pwd());
	if (bltin_pos == 3)
		return(ft_exec_export());
	if (bltin_pos == 4)
		return(ft_exec_unset());
	if (bltin_pos == 5)
		return(ft_exec_env());
	if (bltin_pos == 6)
		return(ft_exec_exit());
	return(0);
}


int 	ft_exec_cmd(t_minishell *minishell, int pos_token)
{
	char **builtin;
	int i;
	int ret;

	ret = 1;
	i = 0;
	builtin = get_built_in();
	while (i < 8)
	{
		if (!ft_strcmp(builtin[i], minishell->tokens[pos_token]))
		{
			ret = ft_exec_builtin(i, minishell);
			break;
		}
		i++;
	}
	if (ret == 1)
	{
		printf("minishell : command not found : %s\n", minishell->tokens[pos_token]);
		exit(-1);
	}
	else
		return(ret);
}