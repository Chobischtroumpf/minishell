/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:02:19 by alessandro        #+#    #+#             */
/*   Updated: 2020/11/27 01:30:31 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_quote(char **token, int i)
{
	char	buffer[LINE_MAX];
	int		j;

	j = -1;
	ft_bzero(buffer, LINE_MAX);
	while (token[++i])
	{
		if (token[i] == '\'')
			while(token[++i] != '\'')
				buffer[++j] = token[i];
		else if (token[i] == '"')
			while (token[++i] != '"')
				if (token[i] == '$')
					i += 1;
				else
					i += check_backslash();			
		else
		{
			if (token[i] == '$')
				i += 1;
			else
				i += check_backslash(buffer, &token[i], j, 1);
		}
		buffer[++j] = '\0';
		return (ft_strdup(buffer));
	}
}

int			ft_dollar_quotes(t_cmd *cmd)
{
	char	*old_arg;
	int		i;
	while (cmd->argv[++i])
	{
		old_arg = cmd->argv[i];
		cmd->argv[i] = check_quote(cmd->argv[i], -1);
		//split d'arg de nathan, faire gaffe a incrementer i pour ne pas repasser dessus avec le checkeur
		free(old_arg);
	}
}
