/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 14:54:50 by ncolin            #+#    #+#             */
/*   Updated: 2020/10/25 16:57:41 by ncolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void		ft_process_args(char **keyvalue);
// {
// 	if
// }

void		ft_export_no_arg(t_minishell *minishell)
{
	t_env	*tmp;

	tmp = minishell->env;
	while (tmp)
	{
		ft_printf("declare -x %s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

int			ft_exec_export(t_cmd *cmd)
{
	t_minishell *minishell;
	char		**key_value;
	char 		**args;
	int 		i;

	minishell = get_minishell();
	args = cmd->argv;
	i = 2;
	if (!args[1])
	{
		ft_export_no_arg(minishell);
		return (EXIT_SUCCESS);
	}
	while (args[i++])
	{
		if (!ft_strchr(args[i], '='))
			continue ;
		key_value = ft_split(args[i], '=');
		//ft_process_args(key_value);
		ft_free_array(key_value);
		write(1,"222", 4);
	}
	return (EXIT_SUCCESS);
}