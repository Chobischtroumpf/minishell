/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:02:19 by alessandro        #+#    #+#             */
/*   Updated: 2021/01/05 17:53:23 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int backslash_checker(char *tokken, char *buffer, int *j, int quote)
{
	int ret;

	ret = 0;
	if (*tokken == '\\' && quote)
	{
		ret = 1;
		if (ft_haschr("$\"\\", tokken[1]))
			buffer[++*j] = *(++tokken);
		else
		{
			buffer[++*j] = *tokken;
			buffer[++*j] = *(++tokken);
		}
	}
	else if (*tokken == '\\')
	{
		ret = 1;
		buffer[++*j] = *(++tokken);
	}
	else
		buffer[++*j] = *tokken;
	return (ret);
}

char	*check_quote(char *token, int i)
{
	char buffer[LINE_MAX];
	int j;

	j = -1;
	ft_bzero(buffer, LINE_MAX);
	while (token[++i])
	{
		if (token[i] == '\'')
			while(token[++i] != '\'')
				buffer[++j] = token[i];
		else if (token[i] == '"')
			while (token[++i] != '"')
			{
				if (token[i] == '$')
					i += process_dollar(&token[i], buffer, &j, 1);
				else
					i += backslash_checker(&token[i], buffer, &j, 1);
			}
		else
		{			
			if (token[i] == '$')
				i += process_dollar(&token[i], buffer, &j, 0);
			else
				i += backslash_checker(&token[i], buffer, &j, 0);
		}
	}
	buffer[++j] = '\0';
	return (ft_strdup(buffer));
}

void remove_all_chars(char *str, char c)
{
	char *pr = str;
	char *pw = str;
	while (*pr)
	{
		*pw = *pr++;
		pw += (*pw != c);
	}
	*pw = '\0';
}

int ft_dollar_quotes(t_cmd *cmd)
{
	char *old_arg;
	int i;
	int splits;

	// i = -1;
	// while (cmd->argv[++i])
	// 	printf("BEFORE : ARG[%d] = |%s|\n", i, cmd->argv[i]);
	// printf("------------------------------------\n");
	i = -1;
	while (cmd->argv[++i])
	{
		old_arg = cmd->argv[i];
		cmd->argv[i] = check_quote(cmd->argv[i], -1);
		splits = ft_is_split(cmd->argv[i]);
		if (splits && cmd->argv[i][0] == 3)
		{
			cmd->argv[i] = ft_substr(cmd->argv[i], 1, ft_strlen(cmd->argv[i])); //used to remove splitting flag. this should be rewritten, probably causing leaks
			cmd->argv = ft_split_args(cmd->argv, i);
			i += splits-1;
		}
		free(old_arg);
	}
	i = -1;
	while (cmd->argv[++i])
		remove_all_chars(cmd->argv[i], 3);
	// i = -1;
	// printf("------------------------------------\n");
	// while (cmd->argv[++i])
	// 	printf("AFTER : ARG[%d] = |%s|\n", i, cmd->argv[i]);
	return (1);
}
