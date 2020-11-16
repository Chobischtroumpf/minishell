/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 11:16:48 by adorigo           #+#    #+#             */
/*   Updated: 2020/11/16 13:34:44 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	ft_is_redir(char *s)
{
	if (!ft_strcmp(s, "<"))
		return (1);
	if (!ft_strcmp(s, ">"))
		return (1);
	if (!ft_strcmp(s, ">>"))
		return (1);
	return (0);
}

/*
** check_redir is a function that will iterate through the tokens, checking
** that there are no double redirections, or redirections followed by a pipe or
** a semi-colon. in case of error, it will call the ft_parse_error function,
** which will print the token at fault
*/

static int
	check_redir(char **tokens)
{
	int i;
	int redi;

	redi = 0;
	i = 0;
	while (tokens[i])
	{
		if (ft_is_redir(tokens[i]))
		{
			redi++;
			if (redi == 2)
				return (ft_parse_error(tokens[i], 0));
		}
		else if (redi == 1 && (!ft_strcmp(tokens[i], ";")
				|| !ft_strcmp(tokens[i], "|")))
			return (ft_parse_error(tokens[i], 0));
		else
			redi = 0;
		i++;
	}
	if (i != 0 && ft_is_redir(tokens[i - 1]))
		return (ft_parse_error("newline", 0));
	return (1);
}

/*
** check_pipe is a function that will iterate through each tokens, and check
** that tere are no double pipes, or pipes followed by either a redirection or
** a semi-colon. in case of error, it will call the ft_parse_error function,
** which will print the token at fault
*/

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
				return (ft_parse_error("|", 0));
			pipe++;
			if (pipe == 2)
				return (ft_parse_error("||", 0));
		}
		else if (pipe == 1 &&
			(ft_is_redir(tokens[i]) || !ft_strcmp(tokens[i], ";")))
			return (ft_parse_error(tokens[i], 0));
		else
			pipe = 0;
		i++;
	}
	if (i != 0 && !ft_strcmp(tokens[i - 1], "|"))
		return (ft_parse_error("|", 0));
	return (1);
}

/*
** the check_semi function check that there are no semi-colons at the begining
** of the line, or two semi-colons following each others
*/

static int
	check_semi(char **tokens)
{
	int i;
	int semi;

	i = 0;
	semi = 0;
	while (tokens[i])
	{
		if (!ft_strcmp(tokens[i], ";"))
		{
			if (i == 0)
				return (ft_parse_error(";", 0));
			semi++;
			if (semi == 2)
				return (ft_parse_error(";", 0));
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
