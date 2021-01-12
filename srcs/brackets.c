/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:02:19 by alessandro        #+#    #+#             */
/*   Updated: 2021/01/12 16:50:53 by adorigo          ###   ########.fr       */
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

static char	*backslash_remover(char *token, int size_token)
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
		}
	return (ft_strdup(buffer));
}

static void	ft_splitting_argv(char **argv, int size_argv, int i, int j)
{
	char	**temp;
	char	*old_arg;
	int		k;

	if (!(get_minishell()->cmd->argv = ft_calloc(size_argv, sizeof(char*))))
		ft_exit_error();
	while (argv[++i])
		if (ft_haschr(argv[i], -1))
		{
			old_arg = ft_strtrim_integral(argv[i], -1);
			temp = ft_lexing(old_arg);
			free(old_arg);
			k = 0;
			while (temp[k])
			{
				old_arg = temp[k];
				temp[k] = backslash_remover(temp[k], ft_strlen(temp[k]) + 1);
				free(old_arg);
				get_minishell()->cmd->argv[j++] = temp[k++];
			}
			free(temp);
		}
		else
			get_minishell()->cmd->argv[j++] = backslash_remover(argv[i],
												ft_strlen(argv[i]) + 1);
}

int			ft_dollar_quotes(t_cmd *cmd)
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
	ft_free_array(get_minishell()->cmd->argv, 0);
	ft_splitting_argv(temp_argv, size_temp_argv + 1, -1, 0);
	ft_free_array(temp_argv, 0);
	return (1);
}
