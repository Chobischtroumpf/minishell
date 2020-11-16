/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 16:59:14 by adorigo           #+#    #+#             */
/*   Updated: 2020/11/16 12:32:33 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** ft_check_sep will check what character line in position i is, in order to
** know how many chars it will need to skip in order to get to the next token
*/

int			ft_check_sep(char *line, int i, int space)
{
	int jump;

	if (line[i] == '>' && line[i + 1] == '>')
		jump = 2;
	else if (line[i] == ' ' || line[i] == '\t' || line[i] == '>' ||
	line[i] == '<' || line[i] == '|' || line[i] == ';')
		jump = 1;
	else
		return (0);
	if (space == 0)
		return (jump);
	else if (space == 1)
	{
		i += jump;
		while (line[i] == ' ' || *line == '\t')
		{
			i++;
			jump++;
		}
		return (jump);
	}
	return (0);
}

/*
** ft_brackets will check if line at position i has a double bracket or single
** bracket, and will make sure that it has an enclosing bracket somewhere at
** the end of the line
*/

int			ft_brackets(char *line, int i)
{
	int		nbr_backslash;

	nbr_backslash = ft_backslash_counter(line, i - 1);
	if (line[i] == '"' && !nbr_backslash)
	{
		while (line[i])
		{
			i++;
			if (line[i] == '"' && !ft_backslash_counter(line, i - 1))
				break;
		}
		if (!line[i])
			return (-1);
	}
	else if (line[i] == '\'' && !nbr_backslash)
	{
		while (line[i])
		{
			i++;
			if (line[i] == '\'')
				break;
		}
		if (!line[i])
			return (-2);
	}
	return (i);
}

/*
** ft_tokens_count will count how many tokens line has, a token being anything
** that is not whitespace
*/

int			ft_tokens_count(char *line)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (!ft_haschr(SEP_SPACE, line[i]) && line[i])
		{
			count++;
			while (!ft_haschr(SEP_SPACE, line[i]) && line[i])
			{
				if ((i = ft_brackets(line, i)) < 0)
					return (i);
				if (!line[i + 1] && ft_backslash_counter(line, i))
					return (-1);
				i++;
			}
		}
		if (ft_haschr(SEP, line[i]))
			count++;
		i += ft_check_sep(line, i, 0);
	}
	return (count);
}

/*
** the ft_tokens_split function take two arguments, char *line, and
** int nbr_token nbr_token indicates the position of the token that needs to be
** taken. The function will parse line, until it either finds the token number
** nbr_token, or reaches the end of the line
*/

char		*ft_tokens_split(char *line, int nbr_token)
{
	int ck;
	int cnt;
	int i;

	cnt = 0;
	ck = 0;
	i = 0;
	while (line[i])
	{
		if (!ft_haschr(SEP_SPACE, line[i]) && line[i] && ++cnt)
		{
			while (!ft_haschr(SEP_SPACE, line[i]) && line[i])
				i = ft_brackets(line, i) + 1;
			if (cnt == nbr_token)
				return (ft_substr(line, ck, i - ck));
			ck = i;
		}
		if (ft_haschr(SEP, line[i]) && ++cnt)
			if (cnt == nbr_token)
				return (ft_substr(line, ck, i + ft_check_sep(line, i, 1) - ck));
		i += ft_check_sep(line, i, 1);
		ck = i;
	}
	return (NULL);
}
