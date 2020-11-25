/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:12:57 by nathan            #+#    #+#             */
/*   Updated: 2020/11/25 15:43:59 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		has_dollar(char *arg)
{
	int i;
	char *str;
	char *tmp;

	i = 0;
	if (ft_strchr(arg, '$'))
	{
		tmp = remove_char(arg, '\"');
		str = ft_strtrim(tmp, " ");
		free(tmp);
	}
	else
		str = ft_strdup(arg);
	while (str[i])
	{
		if (i > 0 && str[i] == '$' && str[i - 1] != '\\' && str[i + 1])
			return (free_str_ret(str));
		else if (str[i] == '$' && str[i + 1] && str[i - 1] != '\\')
			return (free_str_ret(str));
		else if (str[i] == '\'' && !ft_backslash_counter(str, i - 1))
		{
			i++;
			while (str[i] != '\'')
				i++;
		}
		i++;
	}
	free(str);
	return (0);
}

char	*replace_false_dollar(char *arg, int i)
{
	char	*tmp;
	char	*prefix;
	char	*suffix;
	int		j;

	tmp = ft_substr(arg, i, ft_strlen(arg) - i);
	// printf("subs %s\n", tmp);
	j = 0;
	while (tmp[++j])
		if (tmp[j] == '$')
			break ;
	if (j > 0 && tmp[j] == '$' && tmp[j - 1] == '\\')
	{
		free(tmp);
		return (arg);
	}
	prefix = ft_substr(arg, 0, i);
	// printf("prefix %s\n", prefix);
	suffix = ft_substr(tmp, j, ft_strlen(tmp) - j);
	// printf("suffix %s\n", suffix);
	free(arg);
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
	free(arg);
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
			// printf("%s %d\n", arg, i);
			if (!ft_strncmp((arg + i), "$$", 2))
				if (!ft_backslash_counter(arg, i - 1))
					arg = replace_by_env(arg, "42", "TEMP_PID", i);
			if (!ft_strncmp((arg + i), "$?", 2))
				arg = replace_by_env(arg, "42", \
				ft_itoa(get_minishell()->excode), i);
			if (!ft_strncmp((arg + i), key, ft_strlen(key)))
				arg = replace_by_env(arg, key, value, i);
			else if (arg[i] == '$')
			{
				j = 1;
				while (arg[i + j] && arg[i + j] != '$' && !ft_haschr(" \t<>|;\",\']", arg[i + j]))
					j++;
				str = ft_substr(arg, i + 1, j - 1);
				if (!ft_find_by_key(str) && arg[i + 1])
					arg = replace_false_dollar(arg, i);
				free(str);
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

void printoutarray(char **pointertoarray)
{
	int count;
	count = 0;
	while (pointertoarray[count])
		count++;
	for(int i = 0; i < count; i++)
	{
		printf("ARGS[%i] >%s< \n",i, pointertoarray[i]);
	}
}

char	**ft_gros_bordel(char **args, int i)
{
	char **splitted;
	char **new_args;
	int j;
	
	j = 0;
	splitted = ft_split(args[i],' ');
	new_args = malloc(sizeof(char*) * (ft_count_arg(args) + ft_count_arg(splitted) + 2));
	while (j < i)
	{
		new_args[j] = ft_strdup(args[j]);
		j++;
	}
	int k = 0;
	while (splitted[k])
	{
		new_args[j] = ft_strdup(splitted[k]);
		j++;
		k++;
	}
	i++;
	while (args[i])
	{
		new_args[j] = ft_strdup(args[i]);
		i++;
		j++;
	}
	ft_free_array(splitted);
	// ft_free_array(args);
	new_args[j] = NULL;
	// printf("\n-----ARGS AFTER GROS BORDEL-----\n\n");
	// printoutarray(new_args);
	return (new_args);
}

int 	ft_is_split(char * str)
{
	char *tmp;
	int i;

	tmp = ft_strtrim(str, " ");
	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
		{
			free(tmp);
			return (1);
		}
		i++;
	}
	free(tmp);
	return (0);
}

void	check_dollar(t_cmd *cmd)
{
	char	**args;
	int		i;

	i = 0;
	
	args = cmd->argv;
	// printf("-----ARGS BEFORE DOLLAR REMOVAL-----\n\n");
	// printoutarray(args);
	while (args[i])
	{
		while (has_dollar(args[i]))
		{
			args[i] = dollar_to_env(args[i]);
			if (ft_is_split(args[i]))
			{
				// printf("need to be splitted\n");
				cmd->argv = ft_gros_bordel(args, i);
			}
		}
		i++;
	}
	// printf("\n-----ARGS AFTER DOLLAR REMOVAL-----\n\n");
	// printoutarray(args);
}