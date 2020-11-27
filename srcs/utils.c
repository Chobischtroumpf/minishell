/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 18:09:34 by adorigo           #+#    #+#             */
/*   Updated: 2020/11/26 23:55:37 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Joins *char 's1' and *char 's2' with a character 'del' between the two.
*/

char	*ft_strjoin_delimiter(char *s1, char *s2, char del)
{
	char	*str;
	char	*to_free;
	int		total;
	int		i;

	i = 0;
	to_free = s1;
	if (!s1 || !s2)
		return (NULL);
	total = ft_strlen(s1) + ft_strlen(s2) + 2;
	if (!(str = (char *)malloc(total * sizeof(char))))
		return (NULL);
	while (*s1)
		str[i++] = *s1++;
	str[i++] = del;
	while (*s2)
		str[i++] = *s2++;
	str[i] = '\0';
	return (str);
}

int		ft_count_arg(char **arg)
{
	int i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}

int		ft_isascii_except(int c)
{
	if (c >= ' ' && c <= '~' && c != '$' && c != '"' && c != '\\')
		return (0);
	return (1);
}

char	*remove_char(char *str, char c)
{
	char	*new;
	int		i;
	int		j;
	int		l;

	new = ft_strnew(ft_strlen(str));
	i = 0;
	j = 0;
	l = ft_strlen(str);
	while (i < l)
	{
		if (str[i] != c)
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	return (new);
}

int		free_str_ret(char *str)
{
	free(str);
	return (1);
}
