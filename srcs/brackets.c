/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:02:19 by alessandro        #+#    #+#             */
/*   Updated: 2020/12/11 17:32:17 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	backslash_checker(char *tokken, char *buffer, int *j, int quote)
{
	int ret;

	ret = 0;
	if (tokken[0] == '\\' && quote)
	{
		ret = 1;
		if (ft_haschr("$'\"\\", tokken[1]))
			buffer[++*j] = *(++tokken);
		else
		{
			buffer[++*j] = *tokken;
			buffer[++*j] = *(++tokken);
		}
	}
	else if (tokken[0] == '\\')
	{
		ret = 1;
		buffer[++*j] = *(++tokken);
	}
	else
		buffer[++*j] = *tokken;
	return (ret);
}

static int	check_single_quote(char *token, char *buffer, int *j)
{
	int	i;

	i = 1;
	buffer[++*j] = *(token++);
	while(*(token) != '\'' && i++)
		buffer[++*j] = *(token++);
	buffer[++*j] = *(token);
	return (i);
}

static char	*check_quote(char *token, int i)
{
	char	buffer[LINE_MAX];
	int		j;

	j = -1;
	ft_bzero(buffer, LINE_MAX);
	while (token[++i])
	{
		if (token[i] == '\'')
			i += check_single_quote(&token[i], buffer, &j);
		else if (token[i++] == '"')
		{
			while (token[i] != '"')
				if (token[i] == '$')
					i += process_dollar(&token[i], buffer, &j);//replacer l'env, virer les guillemets, placer un délimiteur pour le split, renvoyer la longueur de l'env
				else
					i += backslash_checker(&token[i], buffer, &j, 1);
			buffer[++j] = token[i];
		}
		else
		{
			if (token[i] == '$')
				i += 1;
			else
				i += backslash_checker(&token[i], buffer, &j, 1);
		}
	}
	buffer[++j] = '\0';
	return (ft_strdup(buffer));
}

int			ft_dollar_quotes(t_cmd *cmd)
{
	char	*old_arg;
	int		i;

	i = -1;
	while (cmd->argv[++i])
	{
		old_arg = cmd->argv[i];
		cmd->argv[i] = check_quote(cmd->argv[i], -1);
		//split d'arg de nathan, faire gaffe a incrementer i pour ne pas repasser dessus avec le checkeur
		free(old_arg);
	}
	return (1);
}
