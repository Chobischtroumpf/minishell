/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltin_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 12:58:37 by nathan            #+#    #+#             */
/*   Updated: 2021/01/11 20:58:38 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Ft_valid_key will make sure that the given key to the export command is
**	valid.(Wont start with a digit, '+' ot '=' sign and be only alphanum chars)
*/

int		ft_valid_key(char *str)
{
	int		i;
	char	*special_chars;
	char	*arg;
	int		eq_found;

	arg = ft_strjoin(str, "=");
	eq_found = 0;
	i = 0;
	special_chars = "_+=";
	if (ft_isdigit(arg[0]) || arg[0] == '=' || arg[0] == '+')
		return (free_str_ret(arg, 0));
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && !ft_strchr(special_chars, arg[i]))
			return (free_str_ret(arg, 0));
		if (!eq_found && arg[i] == '+' && arg[i + 1] != '=')
			return (free_str_ret(arg, 0));
		if (arg[i] == '=')
			eq_found++;
		i++;
	}
	free(arg);
	if (eq_found)
		return (1);
	return (0);
}

/*
**	Ft_process_args will process the 'keyvalue' **char passed as argument.
**
**	If a '+' sign is found at the end of the 'key' string it means that
**	the existing value of that key should be appended - not replaced - by
**	the new value (if not existing, a new node is created).
**
**	If the assignement is done with a single '=' sign, a new node is created.
**	In the case the node already existed, it is first deleted, then recreated.
*/

void	ft_process_args(char **keyvalue)
{
	char	*tmp;

	update_lastcmd(keyvalue[0]);
	if ((keyvalue[0][ft_strlen(keyvalue[0]) - 1]) == '+')
	{
		tmp = keyvalue[0];
		keyvalue[0] = ft_strndup(keyvalue[0], ft_strlen(keyvalue[0]) - 1);
		free(tmp);
		if (ft_find_by_key(keyvalue[0]))
			ft_append_env(keyvalue);
		else
			ft_add_env(keyvalue);
	}
	else
	{
		if (ft_find_by_key(keyvalue[0]))
		{
			ft_remove_env(&get_minishell()->env, keyvalue[0]);
			ft_add_env(keyvalue);
		}
		else
			ft_add_env(keyvalue);
	}
	ft_free_array(keyvalue, 0);
}

/*
**	ft_export_no_arg occurs when the export command is called without any
**	argument. It will print each element of the env_list preceded by
**	"declare-x".
*/

int		ft_export_no_arg(t_minishell *minishell)
{
	t_env	*tmp;
	char	*temp;

	tmp = minishell->env;
	while (tmp->next)
	{
		if (ft_haschr("$\"\\", tmp->value[0]) && ft_strlen(tmp->value) == 1)
		{
			temp = ft_strjoin("\\", tmp->value);
			free(tmp->value);
			tmp->value = temp;
		}
		ft_printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

/*
**	Ft_exec_export is the main function to handle the export command of the
**	minishell. If performs a series of checks to determine if the export
**	arguments are existing/valid. Returns (0) on complition.
*/

int		ft_exec_export(t_cmd *cmd)
{
	char	**key_value;
	char	**arg;
	int		i;
	int		ret;

	arg = cmd->argv;
	ret = 0;
	i = 0;
	if (!arg[1])
		return (ft_export_no_arg(get_minishell()));
	while (arg[++i])
	{
		if (!ft_strchr(arg[i], '='))
		{
			if (ft_hasnchar(arg[i], "+=;|&$\"\\' ") || !ft_strlen(arg[i]))
				ret = ft_invalid_id("export", arg[i]);
			continue;
		}
		key_value = ft_split_once(arg[i], '=');
		if (ft_valid_key(key_value[0]))
			ft_process_args(key_value);
		else
			return (ft_free_array(key_value, ft_invalid_id("export", arg[i])));
	}
	return ((ret) ? EXIT_FAILURE : EXIT_SUCCESS);
}

void	update_lastcmd(char *last_cmd)
{
	ft_remove_env(&get_minishell()->env, "_");
	ft_add_env2("_", last_cmd);
}
