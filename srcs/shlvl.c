/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:43:01 by alessandro        #+#    #+#             */
/*   Updated: 2020/11/06 11:52:24 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exec_export_shlvl(char *shlvl)
{
	t_cmd			*cmd;
	char			**argv;

	if (!(cmd = malloc(sizeof(t_cmd*))))
		ft_exit_error();
	if (!(argv = malloc(sizeof(char*) * 3)))
		ft_exit_error();
	argv[0] = ft_strdup("export");
	argv[1] = ft_strjoin("SHLVL=", shlvl);
	argv[2] = NULL;
	cmd->argv = argv;
	ft_exec_export(cmd);
	ft_free_array(argv);
	free(cmd);
}

int			is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i = 1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void		ft_shlvl(void)
{
	char			*shlvl_str;
	long			shlvl;

	shlvl_str = ft_find_by_key2("SHLVL");
	if (!shlvl_str || is_numeric(shlvl_str))
		shlvl_str =	ft_strdup("1");
	else
	{
		shlvl = ft_atoi_pos(shlvl_str);
		if (shlvl < 999)
			shlvl_str = ft_itoa(shlvl + 1);
		else if (shlvl >= 999)
			shlvl_str = ft_strdup(ft_itoa(ft_error_shlvl(shlvl + 1)));
	}
	ft_exec_export_shlvl(shlvl_str);
	free(shlvl_str);
}
