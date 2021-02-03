/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 16:59:14 by adorigo           #+#    #+#             */
/*   Updated: 2021/01/22 10:33:13 by adorigo          ###   ########.fr       */
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

char		*replace_tilde(char *token)
{
	char	*new_token;

	if (token[0] == '~')
	{
		new_token = ft_strdup(ft_find_by_key2("HOME"));
		if (ft_strncmp(&token[1], "/", 1))
			new_token = ft_strjoin_free(new_token, "/");
		new_token = ft_strjoin_doublefree(new_token,
					ft_substr(token, 1, ft_strlen(token) - 1));
		free(token);
		return (new_token);
	}
	else
		return (token);
}

/*
** the ft_tokens_split function take two arguments, char *line, and
** int nbr_token nbr_token indicates the position of the token that needs to be
** taken. The function will parse line, until it either finds the token number
** nbr_token, or reaches the end of the line
*/

char		*ft_tokens_split(char *line, int *idx, int ck, int is_dlr)
{
	char	*token;

	token = NULL;
	if (!ft_haschr(SEP_SPACE, line[*idx]) && line[*idx])
	{
		while (line[*idx] != '\0')
			if (!ft_haschr(SEP_SPACE, line[*idx]))
				*idx = ft_brackets(line, *idx) + 1;
			else if (ft_haschr(SEP_SPACE, line[*idx])
					&& ft_backslash_counter(line, *idx - 1))
				*idx += 1;
			else
				break ;
		token = ft_substr(line, ck, *idx - ck);
	}
	else if (ft_haschr(SEP, line[*idx]))
	{
		token = ft_substr(line, ck, *idx + ft_check_sep(line, *idx, 0) - ck);
		*idx += ft_check_sep(line, *idx, 0);
	}
	while (line[*idx] && ft_haschr(SPACE, line[*idx]))
		(*idx)++;
	if (!is_dlr)
		token = replace_tilde(token);
	return (token);
}
