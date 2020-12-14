/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:12:57 by nathan            #+#    #+#             */
/*   Updated: 2020/12/14 12:52:32 by ncolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		has_dollar(char *arg)
{
	int		i;
	char	*str;
	char	*tmp;

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
			return (free_str_ret(str, 1));
		else if (str[i] == '$' && str[i + 1] && str[i - 1] != '\\')
			return (free_str_ret(str, 1));
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
	suffix = ft_substr(tmp, j, ft_strlen(tmp) - j);
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
				while (arg[i + j] && arg[i + j] != '$' && !ft_haschr(" \\\t<>|;\",\']", arg[i + j]))
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

void	add_str_to_buffer(char *buffer, char *str, int *j)
{
	while(*str)
	{
		buffer[++*j] = *str++;
	}
}

int 	check_part_cases(char *token, char *buffer, int *j)
{
	if (!ft_strncmp(token, "$$", 2))
	{
		add_str_to_buffer(buffer, "TEMP_PID", j);
		return (1);
	}
	else if (!ft_strncmp(token, "$?", 2))
	{
		add_str_to_buffer(buffer, ft_itoa(get_minishell()->excode), j);
		return (1);
	}
	// $ alone
	return (0);
		
}

int		check_env(char *token, char *buffer, int *j)
{
	int len;
	
	len = ft_strlen(token);
	printf("token : %s\n", token);
	printf("buffer : %s\nj : %d\n", buffer, *j);
	while (len--)
	{
		if ()
	}
	return 0;
}

int		process_dollar(char *token, char *buffer, int *j)
{	
	int ret;
	char *token2;
	
	token2 = ft_substr(token, 0, (int)(ft_strchr(token, '"') - token));// gets rid of last "

	if ((ret = check_part_cases(token2, buffer, j)))// handles $$ and $?
		return (ret);
	else if ((ret = check_env(token2, buffer, j))) // is it in env ?
		return (ret);
	// not existent()
	return (ret);
}
