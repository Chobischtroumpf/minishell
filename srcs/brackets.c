/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:02:19 by alessandro        #+#    #+#             */
/*   Updated: 2021/01/12 02:47:01 by adorigo          ###   ########.fr       */
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

void		remove_all_chars(char *str, char c)
{
	char *pr;
	char *pw;

	pr = str;
	pw = str;
	while (*pr)
	{
		*pw = *pr++;
		pw += (*pw != c);
	}
	*pw = '\0';
}

int			ft_dollar_quotes(t_cmd *cmd)
{
	char	**temp_argv;
	char	**splitted_temp_argv;
	char	*untrimmed_argv;
	int		size_temp_argv;
	int		i;
	int		j;
	int		k;

	i = -1;
	if (!(temp_argv = ft_calloc(ft_array_size(cmd->argv) + 1, sizeof(char *))))
		ft_exit_error();
	while (cmd->argv[++i])
		temp_argv[i] = check_quote(cmd->argv[i], -1);
	i = -1;
	size_temp_argv = 0;
	while (temp_argv[++i])
		if (temp_argv[i][0] == -1)
			size_temp_argv += ft_tokens_count(&(temp_argv[i][1]));
		else
			size_temp_argv++;
	ft_free_array(cmd->argv);
	if (!(cmd->argv = ft_calloc(size_temp_argv, sizeof(char *))))
		ft_exit_error();
	i = -1;
	j = 0;
	while (temp_argv[++i])
	{
		if (temp_argv[i][0] == -1)
		{
			untrimmed_argv = temp_argv[i];
			temp_argv[i] = ft_substr(temp_argv[i], 1, ft_strlen(temp_argv[i]));
			free(untrimmed_argv);
			splitted_temp_argv = ft_lexing(temp_argv[i]);
			k = 0;
			while (splitted_temp_argv[k])
				cmd->argv[j++] = splitted_temp_argv[k++];
		}
		else
			cmd->argv[j++] = temp_argv[i];
	}
	return (1);
}
