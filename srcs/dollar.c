/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:12:57 by nathan            #+#    #+#             */
/*   Updated: 2021/01/13 13:48:54 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_str_to_buffer(char *buffer, char *str, int *j, int quote)
{
	int k;

	k = *j;
	if (!quote && ft_haschr(str, ' '))
		skip_extra_spaces(str);
	while (*str)
		buffer[++*j] = *str++;
	if (!quote && buffer[0] != -1)
	{
		k = ++*j;
		while (k >= 0)
		{
			buffer[k + 1] = buffer[k];
			k--;
		}
		buffer[0] = -1;
	}
	else if (quote)
	{
		while (++k <= *j)
		{
			if (buffer[k] == ' ')
				buffer[k] = -3;
		}
	}
}

int		check_part_cases(char *token, char *buffer, int *j, int quote)
{
	char *integer;

	if (!ft_strncmp(token, "$$", 2))
	{
		add_str_to_buffer(buffer, "$$", j, quote);
		return (1);
	}
	else if (!ft_strncmp(token, "$?", 2))
	{
		integer = ft_itoa(get_minishell()->exval);
		add_str_to_buffer(buffer, integer, j, quote);
		free(integer);
		return (1);
	}
	else if (token[0] == '$' && (ft_haschr("\\", token[1]) || !token[1]))
	{
		add_str_to_buffer(buffer, "$", j, quote);
		return (1);
	}
	return (0);
}

int		check_env(char *token, char *buffer, int *j, int quote)
{
	int		len;
	char	*value;
	char	*key;

	len = ft_strpbkr(&token[1], "-!`'\"%^&*()=+|\\<>,./~#@][¬:;$");
	if (len == 0)
		len = ft_strlen(token) - 1;
	key = ft_substr(token, 1, len);
	if ((value = ft_strdup(ft_find_by_key2(key))))
	{
		add_str_to_buffer(buffer, value, j, quote);
		free(key);
		free(value);
		return (len);
	}
	free(key);
	free(value);
	return (0);
}

int		replace_false_dollar(char *token, char *buffer, int *j)
{
	int i;
	int count;

	i = 1;
	count = 0;
	while (token[i] && (ft_isalnum(token[i]) || token[i] == '_'))
	{
		i++;
		count++;
	}
	if (count == 0)
		buffer[++*j] = token[0];
	if (token[i] != '$' && (ft_isalnum(token[i]) || token[i] == '_'))
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
		token2 = ft_substr(token, 0, (int)(ft_strchr(token, '"') - token));
	else
		token2 = ft_strdup(token);
	if ((ret = check_part_cases(token2, buffer, j, quote)))
		return (free_str_ret(token2, ret));
	else if ((ret = check_env(token2, buffer, j, quote)))
		return (free_str_ret(token2, ret));
	else if ((ret = replace_false_dollar(token2, buffer, j)))
		return (free_str_ret(token2, ret));
	free(token2);
	return (ret);
}
