/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:02:19 by alessandro        #+#    #+#             */
/*   Updated: 2021/01/06 23:35:20 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	backslash_checker(char *tokken, char *buffer, int *j, int quote)
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

char		*check_quote(char *token, int i)
{
	char	buffer[LINE_MAX];
	int		j;

	j = -1;
	ft_bzero(buffer, LINE_MAX);
	while (token[++i])
		if (token[i] == '\'')
			while (token[++i] != '\'')
				buffer[++j] = token[i];
		else if (token[i] == '"')
			while (token[++i] != '"')
				if (token[i] == '$')
					i += process_dollar(&token[i], buffer, &j, 1);
				else
					i += backslash_checker(&token[i], buffer, &j, 1);
		else
		{
			if (token[i] == '$')
				i += process_dollar(&token[i], buffer, &j, 0);
			else
				i += backslash_checker(&token[i], buffer, &j, 0);
		}
	buffer[++j] = '\0';
	return (ft_strdup(buffer));
}

int			ft_dollar_quotes(t_cmd *cmd)
{
	char	*old_arg;
	int		i;
	int		splits;

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
		}
		free(old_arg);
	}
	return (1);
}
