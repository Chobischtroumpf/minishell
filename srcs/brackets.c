/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:02:19 by alessandro        #+#    #+#             */
/*   Updated: 2021/01/12 13:53:50 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_out_array(char **pointertoarray)
{
	int count;
	int i;

	i = 0;
	count = 0;
	while (pointertoarray[count])
		count++;
	while (i < count)
	{
		printf("ARGS[%i] >%s< \n", i, pointertoarray[i]);
		i++;
	}
}

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
		buffer[++*j] = *token;
		buffer[++*j] = *(++token);
	}
	else
		buffer[++*j] = *token;
	return (ret);
}

static char	*backslash_remover(char	*token, int size_token)
{
	char	buffer[size_token];
	int		i;
	int		j;

	i = -1;
	j = -1;
	ft_bzero(buffer, size_token);
	while (token[++i])
	{

		// printf("buffer[j] : %c\nj : %d\n i: %d\n", buffer[j], j, i);
	}
	return (ft_strdup(buffer));
}

char		*check_quote(char *token, int i)
{
	char	buffer[LINE_MAX];
	int		j;
	int		k;

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
			{
				i += process_dollar(&token[i], buffer, &j, 0);
				if (buffer[0] != -1)
				{
					k = ++j;
					while (k >= 0)
					{
						buffer[k + 1] = buffer[k];
						k--;
					}
					buffer[0] = -1;
				}
			}
			else
				i += backslash_checker(&token[i], buffer, &j, 0);
		}
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
	char	*trimmed_argv;
	int		size_temp_argv;
	int		i;
	int		j;
	int		k;

	i = -1;
	// print_out_array(cmd->argv);
	if (!(temp_argv = ft_calloc(ft_array_size(cmd->argv) + 1, sizeof(char *))))
		ft_exit_error();
	while (cmd->argv[++i])
		temp_argv[i] = check_quote(cmd->argv[i], -1);
	i = -1;
	size_temp_argv = 0;
	// print_out_array(temp_argv);
	while (temp_argv[++i])
		if (ft_haschr(temp_argv[i], -1))
		{
			size_temp_argv += ft_tokens_count(&(temp_argv[i][1]));
		}
		else
			size_temp_argv++;
	// ft_free_array(cmd->argv, 0);
	if (!(cmd->argv = ft_calloc(size_temp_argv + 1, sizeof(char *))))
		ft_exit_error();
	i = -1;
	j = 0;
	while (temp_argv[++i] )
	{
		if (ft_haschr(temp_argv[i], -1))
		{
			trimmed_argv = ft_strtrim_integral(temp_argv[i], -1);
			splitted_temp_argv = ft_lexing(trimmed_argv);
			//here
			k = 0;
			while (splitted_temp_argv[k])
			{
				splitted_temp_argv[k] = backslash_remover(splitted_temp_argv[k], ft_strlen(splitted_temp_argv[k]) + 1);
				cmd->argv[j++] = splitted_temp_argv[k++];
			}
		}
		else
			cmd->argv[j++] = temp_argv[i];
	}
	return (1);
}
