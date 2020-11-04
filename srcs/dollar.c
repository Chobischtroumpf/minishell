/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:12:57 by nathan            #+#    #+#             */
/*   Updated: 2020/11/04 12:29:55 by nathan           ###   ########.fr       */
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
	int		i;

	tmp = get_minishell()->env;
	while (tmp)
	{
		i = 0;
		key = ft_strjoin("$", tmp->key);
		value = ft_strdup(tmp->value);
		while (arg[i])
		{
			if (!ft_strncmp((arg + i), "$$", 2))
				arg = replace_by_env(arg, "42", "TEMP_PID", i);
			else if (!ft_strncmp((arg + i), "$?", 2))
				arg = replace_by_env(arg, "42", ft_itoa(get_minishell()->excode), i);
			else if (!ft_strncmp((arg + i), key, ft_strlen(key)))
			{
				if (arg[i + ft_strlen(key)] != '$' && arg[i + ft_strlen(key)] != '\0')
					i++;
				else
					arg = replace_by_env(arg, key, value, i);
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
			args[i] = dollar_to_env(args[i]);
		
		i++;
	}
	
	//remove_single_quote
}
