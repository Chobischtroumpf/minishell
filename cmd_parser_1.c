/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 11:16:48 by adorigo           #+#    #+#             */
/*   Updated: 2020/05/13 12:21:10 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	is_redir(char *s)
{
	if (ft_strcmp(s, "<"))
		return (1);
	if (ft_strcmp(s, ">"))
		return (1);
	if (ft_strcmp(s, ">>"))
		return (1);
	return (0);
}

static int
	check_redir(char **tokens)
{
	int i;
	int redi;

	redi = 0;
	i = 0;
	while (tokens[i])
	{
		if (is_redir(tokens[i]))
		{
			redi++;
			if (redi == 2)
				return (parse_error(tokens[i], 0));
		}
		else if (redi == 1 && (!ft_strcmp(tokens[i], ";")
				|| !ft_strcmp(tokens[i], "|")))
			return (parse_error(tokens[i], 0));
		else
			redi = 0;
		i++;
	}
	if (i != 0 && is_redir(tokens[i - 1]))
		return (parse_error("\\n", 0));
	return (1);
}

static int
	check_pipe(char **tokens)
{
	int pipe;
	int i;

	pipe = 0;
	i = 0;
	while (tokens[i])
	{
		if (!ft_strcmp(tokens[i], "|"))
		{
			if (i == 0)
				return (parse_error("|", 0));
			pipe++;
			if (pipe == 2)
				return (parse_error("|", 0));
		}
		else if (pipe == 1 &&
			(is_redir(tokens[i]) || !ft_strcmp(tokens[i], ";")))
			return (parse_error(tokens[i], 0));
		else
			pipe = 0;
		i++;
	}
	if (i != 0 && !ft_strcmp(tokens[i - 1], "|"))
		return (parse_error("|", 0));
	return (1);
}

static int
	check_semi(char **tokens)
{
	int i;
	int semi;

	i = 0;
	semi = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], ";"))
		{
			if (i == 0)
				return (parse_error(";", 0));
			semi++;
			if (semi == 2)
				return (parse_error(";", 0));
		}
		else
			semi = 0;
		i++;
	}
	return (1);
}

int
	ft_check_tokens(char **tokens)
{
	if (check_redir(tokens)
		&& check_pipe(tokens)
		&& check_semi(tokens))
		return (1);
	return (0);
}
