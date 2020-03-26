/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 16:59:14 by adorigo           #+#    #+#             */
/*   Updated: 2020/03/26 12:10:37 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_jump_spaces(char *line, int i, int jump)
{
	i += jump;
	while (line[i] == ' ' || *line == '\t')
	{
		i++;
		jump++;
	}
	return(jump);
}

int			ft_check_separator(char *line, int i, int space)
{
	int jmp;

	if (line[i] == ' ' || line[i] == '\t')
		jmp = 1;
	else if (line[i] == '>' && line[i + 1] == '>')
		jmp = 2;
	else if (line[i] == '>')
		jmp = 1;
	else if (line[i] == '<')
		jmp = 1;
	else if (line[i] == '|')
		jmp = 1;
	else if (line[i] == ';')
		jmp = 1;
	else
		return (0);
	if (space == 0)
		return (jmp);
	else if (space == 1)
		return (ft_jump_spaces(line, i, jmp));
	return (0);
}

static int	ft_is_backslash(char *line, int *i)
{
	if (!line[*i])
		return (0);
	if (line[*i] == '\\')
		++*i;
	else if (line[*i] == '\"')
		return (0);
	return (1);
}

int			ft_brackets(char *line, int i)
{
	if (line[i] == '\"' &&(i == 0 ||  line[i - 1] != '\\'))
	{
		i++;
		while(ft_is_backslash(line, &i))
			i++;
		if (line[i] == '\0')
			return(-1);
	}
	else if (line[i] == '\'')
	{
		i++;
		while (line[i] != '\'' && line[i])
			i++;
		if (line[i] == '\0')
			return (-1);
	}
	return (i);
}

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
				if ((i = ft_brackets(line, i)) == -1)
				{
					ft_printf("you need to close the brackets\n");
					return (-1);
				}
				if (line[i] == '\\' && !line[i + 1])
					return (-1);
				i++;
			}
		}
		if (ft_haschr(SEP, line[i]))
			count++;
		i += ft_check_separator(line, i, 1);
	}
	return(count);
}


//quand j'assigne, si \ et juste apres ", je met " a la place de \ dans mon char *, et j'incremente.
//l'incrementation normale doit se faire dans la condition, sinon je dois incrémenté de 2

char	*ft_tokens_split(char *line, int nbr_token)
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
		{
			if (cnt == nbr_token)
				return (ft_substr(line, ck, i + ft_check_separator(line, i, 1) - ck));
		}
		i += ft_check_separator(line, i, 2);
		ck = i;
	}
	return (NULL);
}