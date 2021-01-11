/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 16:59:14 by adorigo           #+#    #+#             */
/*   Updated: 2021/01/11 14:59:07 by adorigo          ###   ########.fr       */
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
	printf("i dans ft_brackets : %d\n", i);
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

char		*ft_tokens_split(char **line)
{
	char	*token;
	char	*tmp_line;
	int		i;

	i = 0;
	token = NULL;
	printf("line = %s\n", *line);
	if (!ft_haschr(SEP_SPACE, *line[i]) && *line[i])
	{
		printf("i before while : %d\n", i);
		while (*line[i] != '\0' && printf("condition one ok\n") && !ft_haschr(SEP_SPACE, *line[i]) && printf("condition two ok\n")
			&& !ft_backslash_counter(*line, i - 1) && printf("condition three ok\n"))
		{
			printf("i inside while : %d\n", i);
			i = ft_brackets(*line, i) + 1;
			printf("line[i] = %c\n", *line[i]);
		}
		printf("i after while : %d\n", i);
		token = ft_substr(*line, 0, i);
	}
	else if (ft_haschr(SEP, *line[i]))
	{
		printf("i before token substr : %d\n", i);
		token = ft_substr(*line, 0, ft_check_sep(*line, i, 0));
		i += ft_check_sep(*line, i, 0);
	}
	printf("%d\n", i);
	tmp_line = ft_substr(*line, i, ft_strlen(*line) - i);
	free(*line);
	*line = ft_strtrim(tmp_line, " \t");
	free(tmp_line);
	return (token);
}
