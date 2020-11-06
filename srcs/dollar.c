/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:12:57 by nathan            #+#    #+#             */
/*   Updated: 2020/11/06 10:04:30 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		has_dollar(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
		}
		i++;
	}
	return (0);
}

char	*replace_false_dollar(char *arg, int i)
{
	char	*tmp;
	char	*prefix;
	char	*suffix;
	int		j;

	tmp = ft_substr(arg, i, ft_strlen(arg) - i);
	j = 0;
	while (tmp[++j])
		if (tmp[j] == '$')
			break ;
	prefix = ft_substr(arg, 0, i);
	suffix = ft_substr(tmp, j, ft_strlen(tmp) - j);
	arg = ft_strjoin_free(prefix, suffix);
	free(tmp);
	free(suffix);
	return (arg);
}

char	*replace_by_env(char *arg, char *key, char *value, int i)
{
	char	*prefix;
	int		suffix_start;
	char	*suffix;

	suffix_start = i + ft_strlen(key);
	prefix = ft_substr(arg, 0, i);
	suffix = ft_substr(arg, suffix_start, ft_strlen(arg) - suffix_start);
	prefix = ft_strjoin_free(prefix, value);
	arg = ft_strjoin_free(prefix, suffix);
	free(suffix);
	return (arg);
}

char	*dollar_to_env(char *arg)
{
	t_env	*tmp;
	char	*key;
	char	*value;
	char	*str;
	int		i;
	int		j;

	tmp = get_minishell()->env;
	while (tmp)
	{
		i = 0;
		key = ft_strjoin("$", tmp->key);
		value = ft_strdup(tmp->value);
		while (arg[i])
		{
			i = ft_skip_quotes(arg, i);
			if (!ft_strncmp((arg + i), "$$", 2))
				arg = replace_by_env(arg, "42", "TEMP_PID", i);
			if (!ft_strncmp((arg + i), "$?", 2))
				arg = replace_by_env(arg, "42", \
				ft_itoa(get_minishell()->excode), i);
			if (!ft_strncmp((arg + i), key, ft_strlen(key)))
				arg = replace_by_env(arg, key, value, i);
			else if (arg[i] == '$')
			{
				j = 1;
				while (arg[i + j] && arg[i + j] != '$')
					j++;
				str = ft_substr(arg, i + 1, j - 1);
				if (!ft_find_by_key(get_minishell(), str))
					arg = replace_false_dollar(arg, i);
				break ;
			}
			i++;
		}
		free(key);
		free(value);
		tmp = tmp->next;
	}
	return (arg);
}

void	check_dollar(t_cmd *cmd)
{
	char	**args;
	int		i;

	i = 0;
	args = cmd->argv;
	while (args[i])
	{
		while (has_dollar(args[i]))
			args[i] = dollar_to_env(args[i]);
		i++;
	}
}
