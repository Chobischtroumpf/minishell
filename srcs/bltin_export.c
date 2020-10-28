/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 14:54:50 by ncolin            #+#    #+#             */
/*   Updated: 2020/10/28 13:29:55 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_append_env(t_minishell *minishell, char **keyvalue)
{
	t_env	*tmp;
	char	*new;

	tmp = ft_find_by_key(minishell, keyvalue[0]);
	if (!(new = (char *)malloc(ft_strlen(tmp->value) + \
								ft_strlen(keyvalue[1] + 1))))
		exit(0);
	tmp->value = ft_strjoin_free(tmp->value, keyvalue[1]);
}

int		ft_valid_key(char *arg)
{
	int		i;
	char	*special_chars;
	int		eq_found;

	eq_found = 0;
	i = 0;
	special_chars = "\'\"+=";
	if (ft_isdigit(arg[0]) || arg[0] == '=' || arg[0] == '+')
		return (0);
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && !strchr(special_chars, arg[i]))
			return (0);
		if (!eq_found && arg[i] == '+' && arg[i + 1] != '=')
			return (0);
		if (arg[i] == '=')
			eq_found++;
		i++;
	}
	if (eq_found)
		return (1);
	return (0);
}

void	ft_process_args(char **keyvalue)
{
	char	*tmp;

	if ((keyvalue[0][ft_strlen(keyvalue[0]) - 1]) == '+')
	{
		tmp = keyvalue[0];
		keyvalue[0] = ft_strndup(keyvalue[0], ft_strlen(keyvalue[0]) - 1);
		free(tmp);
		if (ft_find_by_key(get_minishell(), keyvalue[0]))
			ft_append_env(get_minishell(), keyvalue);
		else
			ft_add_env(get_minishell(), keyvalue);
	}
	else
		ft_add_env(get_minishell(), keyvalue);
}

int		ft_export_no_arg(t_minishell *minishell)
{
	t_env	*tmp;

	tmp = minishell->env;
	while (tmp)
	{
		ft_printf("declare -x %s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

int		ft_exec_export(t_cmd *cmd)
{
	char		**key_value;
	char		**args;
	int			i;

	args = cmd->argv;
	i = 1;
	if (!args[i])
		return (ft_export_no_arg(get_minishell()));
	while (args[i])
	{
		if (!ft_strchr(args[i], '='))
		{
			i++;
			continue ;
		}
		if (ft_valid_key(args[i]))
		{
			key_value = ft_split_once(args[i], '=');
			ft_process_args(key_value);
			ft_free_array(key_value);
		}
		else
			ft_invalid_identifier("export", args[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
