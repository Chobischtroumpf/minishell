/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 16:59:14 by adorigo           #+#    #+#             */
/*   Updated: 2021/01/13 13:28:12 by nathan           ###   ########.fr       */
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
	if (space == 1)
	{
		i += jump;
		while (line[i] == ' ' || *line == '\t')
		{
			i++;
			jump++;
		}
		return (jump);
	}
	else
		return (jump);
}

/*
** ft_brackets will check if line at position i has a double bracket or single
** bracket, and will make sure that it has an enclosing bracket somewhere at
** the end of the line
*/

int			ft_brackets(char *line, int i)
{
	if (line[i] == '"' && !ft_backslash_counter(line, i - 1))
	{
		while (line[i])
		{
			i++;
			if (line[i] == '"' && !ft_backslash_counter(line, i - 1))
				break ;
		}
		if (!line[i])
			return (-1);
	}
	else if (line[i] == '\'' && !ft_backslash_counter(line, i - 1))
	{
		while (line[i])
		{
			i++;
			if (line[i] == '\'')
				break ;
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
			while (!(ft_haschr(SEP_SPACE, line[i]) &&
				!ft_backslash_counter(line, i - 1)) && line[i])
			{
				if ((i = ft_brackets(line, i)) < 0)
					return (i);
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

char		*ft_tokens_split(char *line, int *indx)
{
	char	*token;
	int		ck;

	ck = *indx;
	token = NULL;
	if (!ft_haschr(SEP_SPACE, line[*indx]) && line[*indx])
	{
		while (line[*indx] != '\0')
			if (!ft_haschr(SEP_SPACE, line[*indx]))
				*indx = ft_brackets(line, *indx) + 1;
			else if (ft_haschr(SEP_SPACE, line[*indx])
					&& ft_backslash_counter(line, *indx - 1))
				*indx += 1;
			else
				break ;
		token = ft_substr(line, ck, *indx - ck);
	}
	else if (ft_haschr(SEP, line[*indx]))
	{
		token = ft_substr(line, ck, *indx + ft_check_sep(line, *indx, 0) - ck);
		*indx += ft_check_sep(line, *indx, 0);
	}
	while (line[*indx] && ft_haschr(SPACE, line[*indx]))
		(*indx)++;
	return (token);
}
