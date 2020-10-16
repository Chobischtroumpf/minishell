/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 12:08:19 by adorigo           #+#    #+#             */
/*   Updated: 2020/05/14 14:53:02 by adorigo          ###   ########.fr       */
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
		return (1);
	}
	ft_printf("%s\n", cwd);
	return (0);
}


static int	ft_exec_builtin(int bltin_pos)
{
	t_minishell *minishell;

	minishell = get_minishell();
	if (bltin_pos == 0)
		return (ft_exec_echo(minishell->cmd));
	// if (bltin_pos == 1)
		// return (ft_exec_cd(minishell->tokens));
	if (bltin_pos == 2)
		return (ft_exec_pwd());
	// if (bltin_pos == 3)
	// 	return (ft_exec_export());
	// if (bltin_pos == 4)
	// 	return (ft_exec_unset());
	// if (bltin_pos == 5)
	// 	return (ft_exec_env());
	if (bltin_pos == 6)
		return (ft_exec_exit(minishell->cmd));
	return (0);
}

int			ft_exec_cmd(void)
{
	char	**builtin;
	int		i;
	int		ret;

	ret = 1;
	i = -1;
	builtin = get_built_in();
	while (++i < 7)
		if (!ft_strcmp(builtin[i], get_minishell()->cmd->argv[0]))
		{
			ret = ft_exec_builtin(i);
			break ;
		}
	if (ret == 1)
	{
		ft_printf("minishell : command not found : %s\n",
						get_minishell()->cmd->argv[0]);
		return (0);
	}
	else
		return (ret);
}
