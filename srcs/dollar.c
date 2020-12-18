/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:12:57 by nathan            #+#    #+#             */
/*   Updated: 2020/12/18 15:14:36 by nathan           ###   ########.fr       */
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
				// if (!ft_find_by_key(str) && arg[i + 1])
				// 	arg = replace_false_dollar(arg, i);
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

void skip_spaces(char *str)
{
	char *trimmed;
	char *untrimmed;
	int prev_space;
	// printf("before trim |%s|\n", str);
	trimmed = str;
	untrimmed = str;
	prev_space = 0;
	while (*untrimmed)
	{
		if (ft_isspace(*untrimmed))
		{
			if (!prev_space)
			{
				*trimmed++ = ' ';
				prev_space = 1;
			}
		}
		else
		{
			*trimmed++ = *untrimmed;
			prev_space = 0; 
		}
		++untrimmed;
	}
	*trimmed = '\0';
	// printf("after  trim |%s|\n", str);

}

void	add_str_to_buffer(char *buffer, char *str, int *j, int quote)
{
	int flag;
	
	if (!quote)
		skip_spaces(str);
	if (ft_is_split(str))
		flag = 1;
	else
		flag = 0;
	if (flag && !quote)
		buffer[++*j] = 3;
	while(*str)
	{
		buffer[++*j] = *str++;
	}
}

int 	check_part_cases(char *token, char *buffer, int *j, int quote)
{
	if (!ft_strncmp(token, "$$", 2))
	{
		add_str_to_buffer(buffer, "TEMP_PID", j, quote);
		return (1);
	}
	else if (!ft_strncmp(token, "$?", 2))
	{
		add_str_to_buffer(buffer, ft_itoa(get_minishell()->excode), j, quote);
		return (1);
	}
	// $ alone
	return (0);
		
}

int		check_env(char *token, char *buffer, int *j, int quote)
{
	// printf("TOKEN = |%s|\n", token);
	int len;
	char *value;
	len = ft_strlen(token);
	while (len--)
	{
		if ((value = ft_find_by_key2(ft_substr(token,1 , len) )) && (!ft_haschr("_", token[len + 1]) || !token[len + 1]))
		{
			add_str_to_buffer(buffer, value, j, quote);
			// if(!quote)
			// 	skip_spaces(buffer);
			return (len);
		}
	}
	

	return 0;
}

int 	replace_false_dollar(char *token, char *buffer, int *j)
{
	int i;
	int count;
	
	i = 1;
	count =0;
	while (token[i] && !ft_haschr("|", token[i]))
	{
		i++;
		count++;
	}
	if (token[i] != '$' && token[i]!= '|')
		while (token[i])
			buffer[++*j] = token[i++];
	return (count);
}



int		process_dollar(char *token, char *buffer, int *j, int quote)
{	
	int		ret;
	char	*token2;
	
	ret = 0;
	if (quote)
		token2 = ft_substr(token, 0, (int)(ft_strchr(token, '"') - token));// gets rid of last "
	
	else
		token2 = ft_strdup(token);
	
	if ((ret = check_part_cases(token2, buffer, j, quote)))// handles $$ and $?
		return(free_str_ret(token2, ret));
	else if ((ret = check_env(token2, buffer, j, quote))) // is it in env ?
		return(free_str_ret(token2, ret));
	else if ((ret = replace_false_dollar(token2, buffer, j))) // if not in env, get rid off the false key
		return(free_str_ret(token2, ret));
	free(token2);
	return (ret);
}
