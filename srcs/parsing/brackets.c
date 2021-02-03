/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:02:19 by alessandro        #+#    #+#             */
/*   Updated: 2021/02/03 17:33:20 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	backslash_checker(char *token, char *buffer, int *j, int quote)
{
	int ret;

	ret = 0;
	if (*token == '\\' && quote)
	{
		ret = 1;
		if (ft_haschr("$\"\\", token[1]))
			buffer[++*j] = *(++token);
		else
		{
			buffer[++*j] = *token;
			buffer[++*j] = *(++token);
		}
	}
	else if (*token == '\\')
	{
		ret = 1;
		buffer[++*j] = -2;
		buffer[++*j] = *token;
		buffer[++*j] = *(++token);
	}
	else
		buffer[++*j] = *token;
	return (ret);
}

static char	*rm_backslash(char *token, int size_token)
{
	char	buffer[size_token];
	int		i;
	int		j;

	i = -1;
	j = -1;
	ft_bzero(buffer, size_token);
	while (token[++i])
	{
		if (token[i] == -2)
		{
			i += 2;
			buffer[++j] = token[i];
		}
		else if (token[i] == -3)
			buffer[++j] = ' ';
		else
			buffer[++j] = token[i];
	}
	return (ft_strdup(buffer));
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
			if (!token[i])
				break;
		}
	return (ft_strdup(buffer));
}

static void	ft_splitting_argv(t_cmd *cmd, char **argv, int size_argv, int i)
{
	char	**tmp;
	char	*old_arg;
	int		k;
	int		j;

	j = 0;
	if (!(cmd->argv = ft_calloc(size_argv, sizeof(char*))))
		ft_exit_error();
	while (argv[++i])
		if (ft_haschr(argv[i], -1))
		{
			old_arg = ft_strtrim_integral(argv[i], -1);
			tmp = ft_lexing(old_arg, 1);
			free(old_arg);
			k = -1;
			while (tmp[++k])
			{
				old_arg = tmp[k];
				cmd->argv[j++] = rm_backslash(tmp[k], ft_strlen(tmp[k]) + 1);
				free(old_arg);
			}
			free(tmp);
		}
		else
			cmd->argv[j++] = rm_backslash(argv[i], ft_strlen(argv[i]) + 1);
}

void		ft_dollar_quotes(t_cmd *cmd)
{
	char	**temp_argv;
	int		size_temp_argv;
	int		i;

	i = -1;
	if (!(temp_argv = ft_calloc(ft_array_size(cmd->argv) + 1, sizeof(char *))))
		ft_exit_error();
	while (cmd->argv[++i])
		temp_argv[i] = check_quote(cmd->argv[i], -1);
	i = -1;
	size_temp_argv = 0;
	while (temp_argv[++i])
		if (ft_haschr(temp_argv[i], -1))
			size_temp_argv += ft_tokens_count(&(temp_argv[i][1]));
		else
			size_temp_argv++;
	ft_free_array(cmd->argv, 0);
	ft_splitting_argv(cmd, temp_argv, size_temp_argv + 1, -1);
	ft_free_array(temp_argv, 0);
}
